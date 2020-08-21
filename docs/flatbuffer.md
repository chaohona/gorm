https://github.com/halfrost/Halfrost-Field/blob/master/contents/Protocol/FlatBuffers-schema.md#7-file-identification-and-extension

FlatBuffers 与 Protocol Buffers 比较相似，主要的区别在于 FlatBuffers 在访问数据之前不需要解析/解包。两者代码也是一个数量级的。
但是 Protocol Buffers 既没有可选的文本导入/导出功能，也没有 union 这个语言特性，这两点 FlatBuffers 都有。

1、Table
Table是在FlatBuffer中定义对象的主要方式，由一个名称和一个字段列表组成。
每个字段都有一个名称，一个类型和一个可选的默认值（如果省略，它默认为0/NULL）。
Table中每个字段都是可选optional的：它不必出现在wire表示中，并且可以选择省略每个单独对象的字段。
因此可以灵活地添加字段而不用担心数据膨胀。这种设计也是FlatBuffer的前向和后向兼容机制。

table { c:int a:int; b:int; }
带字段顺序的IDL定义方式
table { c:int (id: 2); a:int (id: 0); b:int (id: 1); }
引入id以后，table中的字段顺序就无所谓了，新的与旧的schema完全兼容，只要我们保留id序列即可。

可以向schema的末尾添加字段。不能从schema中删除不在使用的字段，可以将它们标记为deprecated，被标记的字段不会再生成C++的访问器，从而强制该字段不再被使用。
table { a:int (deprecated); b:int; }

为了解决数据结构变更的问题，table通过vtable简介访问字段。每个table都带有一个vtable，
（可以在具有相同布局的多个table之间共享），并且包含存储此特定类型vtable实例的字段的信息。
vtable还可能表示该字段不存在。

table的内存开销很小（因为vtables很小并且共享）访问成本也很小（间接访问），但是提供了很大的灵活性。
table甚至可能比等价的struct花费更少的内存，因为字段在等于默认值时不需要存储在buffer中。

2、Structs
structs和table非常相似，只是structs没有任何字段是可选的（所以也没有默认值），字段可能不会被添加或被弃用。
结构可能只包含标量或其他结构。如果确定以后不会进行任何更改，请将其用于简单对象。
structs使用的内存少于table，并且访问速度更快（它们总是以串联方式存储在其父对象中，并且不使用虚拟表）。
structs不提供前向/后向兼容性，但占用内存更小。对于不太可能该表的对象(例如坐标对活RGBA颜色)存成structs是非常有用的。

3、Types
FlatBuffers支持的标量类型有以下几种：
8bits:	byte(int8),ubyte(uint8),bool
16bits:	short(int16),ushort(uint16)
32bits:	int(int32),uint(uint32),float(float32)
64bits:	long(int64),ulong(uint64),double(float64)
括号里面的名字对应的是类型的别名

FlatBuffers支持的非标量类型有以下几种：
任何类型的数组。不过不支持嵌套数组，可以用table内定义数组的方式来取代嵌套数组。
UTF-8和7-bit ASCII的字符串。其它格式的编码字符串或者二进制数据，需要用[byte]或者[ubyte]来替代。
table、structs、enums、unions

标量类型的字段有默认值，非标量的字段（string/vector/table）如果没有值的话，默认值为NULL。

type = bool | byte | ubyte | short | ushort | int | uint | float | long | ulong | double | int8 | uint8 | int16 | uint16 | int32 | uint32| int64 | uint64 | float32 | float64 | string | [ type ] | ident

4、Enums
定义一系列命名常亮，每个命名常量可以分别给一个定值，也可以默认的从前一个值增加一。默认的第一个值为0.

5、Unions
Unions可以向Enums一样共享许多属性，但不是常量的新名称，二十使用table的名称。
可以声明一个Unions字段，该字段可以包含对这些类型中任何一个的引用，即这块内存区域只能由其中一种类型使用。
另外还会生成一个带有后缀_type的隐藏字段，该字段包含相应的枚举值，从而可以在运行时知道要将哪些类型转换为类型。

union跟enum比较类似，但是union包含的是table，enum包含的是scalar或者struct。

Unions是一种能够在一个FlatBuffer中发送多种消息类型的好方法。
请注意，因为union字段实际上是两个字段（有一个隐藏字段），所以它必须始终是表的一部分，它本身不能作为FlatBuffer的root。


5、Root type
声明了你认为是序列化数据的根表（或结构）。这对于解析不包含对象类型信息的JSON数据尤为重要。

6、File extension
默认情况下，flatc 会将二进制文件输出为 .bin。schema 中的这个声明会将其改变为任何你想要的：
file_extension "ext";

7、RPC interface declarations
rpc_service MonsterStorage {
  Store(Monster):StoreResponse;
  Retrieve(MonsterId):Monster;
}
可以通过--grpc编译参数

8、Attributes
Attributes可以附加到字段声明，放在字段后面或者table/structs/enum/union的名称之后。这些字段可能有也有可能没有值。

一些Attributes只能被编译器识别，比如deprecated。用户可以自定义一些Attributes，但是需要提前进行Attributes声明。
声明以后可以在运行时解析schema的时候进行查询。

目前最新版能识别11中Attributes
(1)id:n(on a table field)
一旦启用了这个id标识符，那么所有字段都必须使用id标识，并且id必须是从0开始的连续数字。
需要特别注意Union，由于Union是由2个字符构成的，并且隐藏字段是排在union字段的前面。
添加了id标识符以后，字段在schema内部的相互顺序就不重要了。新字段用的id必须是紧接着的写一个可用的id（id不能跳，必须是连续的）。
(2)deprecated(on a field)
代表不再为此字段生成访问器，代码应停止使用此数据。旧数据可能扔包含字段，但不能再通过新的代码去访问这个字段。
(3)required(on a non-scalar table field)
required代表该字段不能被省略。默认情况下，所有字段都是可选的，即可以省略。如果构造代码没有初始化这个字段，他们将得到一个断言，并提示缺少必要的字段。
(4)force_align:size (on a struct)
代表强制这个结构体对其比它自然对齐的要高。如果buffer创建的时候是以force_align声明创建的，那么里面的所有structs都会被强制对齐。
(5)bit_flags(on a enum)
这个字段的值表示比特，这意味着在schema中指定的任何值N最终代表1<<N，或者默认不指定值的情况下，将默认得到序列1,2,4,8,...
(6)nested_flatbuffer:"table_name"(on a field)
代表该字段（必须是ubyte的数组）嵌套包含flatbuffer数据，其根类型由table_name给出。生成的代码将为嵌套的FlatBuffer生成一个方便的访问器。
(7)flexbuffer(on a field)
flexbuffer表示该字段(必须是ubyte的数组)包含flexbuffer数据。生成的代码将为FlexBuffer的root创建一个方便的访问器。
(8)key(on a field)
用于当前table中，对其所在类型的数组进行排序时用作关键字。可用于就地查找二进制搜索。
(9)hash(on a field)
这是一个不带符号的32/64为整数字段，因为在JSON解析过程中它的值允许为字符串，然后将其存储为其哈希。属性的值是要使用的散列算法，即使用fnv1_32、fnv1_64、fnv1a_32、fnv1a_64其中之一。
(10)original_order(on a table)
由于表中的元素不需要以任何特定的顺序存储，因此通常为了优化空间，而对他们大小进行排序。而original_order阻止了这种情况发生。通常应该没有任何理由使用这个标志。
(11)'native_*'
已经添加了几个属性来支持基于C++对象的API，所有这些属性都已"native_*"作为前缀

9、FlatBuffers命名规范
Table、struct、enum and rpc names(types)采用大写驼峰命名法。
Table and struct field names采用下划线命名法。这样做方法自动生成小写驼峰命名的代码。
Enum values采用大写驼峰命名法
namespaces 采用大写驼峰命名法

大括号：与声明的开头位于同一行
间距：	缩进2个空格。:两边没有空格，=两边各一个空格。

10、


