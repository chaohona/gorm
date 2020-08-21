## 专为游戏设计的持久化接入层

### 怎么使用(示例见example目录，下面为具体步骤)
> 1、填写数据结构配置文件，文件格式为xml，见gorm-db.xml<br/>
  支持的数据类型int8,uint8,int16,int32,int,int64,uint16,uint32,uint64,double,string,blob,char<br/>
> 2、将1中填写的配置文件转为SQL与C++结构体(protobuffer格式的结构体)<br/>
     2.1 使用工具gorm-conv将xml转换为C++代码文件与protobuff文件<br/>
     2.2 使用protoc将protobuff文件生成代码文件<br/>
         proto版本使用不同有可能编译不过，所以发布版本中没有带protobuff相关的包，可以选择和项目相同的版本使用<br/>
     2.3 利用上面两步生成的代码文件生成动态链接库<br/>
> 3、使用上面2中生成的动态链接库，操作持久化数据<br/>
     动态链接库包括两个:<br/>
     一个为gorm-client.so/gorm-client.a，这个为客户端功能库，这个库是随版本提供的功能库，需要编译在客户端中<br/>
     一个为根据表结构生成的gorm-tables.so/gorm-tables.a，这个库客户端和服务器都需要，当有表结构变更的时候需要生成这个库，重启服务器(后期会改为动态加载)<br/>
> 4、启动服务器<br/>
     4.1 将conf/gorm-server.yml.example 改成conf/gorm-server.yml，修改其中监听端口号<br/>
     4.2 将conf/gorm-db.yml.example 改成conf/gorm-db.yml并修改其中mysql的地址为自己的地址<br/>
     4.3 将动态链接库的路径lib/gorm与lib/mysql-connector的路径加入运行时搜索路径中<br/>
         cat $(pwd)/lib/gorm > /etc/ld.so.conf.d/gorm.conf<br/>
         cat $(pwd)/lib/mysql-connector >> /etc/ld.so.conf.d/gorm.conf<br/>
         ldconfig<br/>
     4.3 将run.sh.example改成run.sh。并执行. run.sh启动gorm-server<br/>
     4.4 查看log.txt中日志，是否启动成功<br/>
> 5、参考example目录中示例编写客户端代码<br/>
     编译gorm-tables库的时候目前需要和src/tables目录中的代码一起编译(后期会将去掉)<br/>
     其中gorm_pb_tables_inc、gorm_table_field_map_define和自定义表文件相关的文件(例如gorm-db.pb.cc)都是动态生成的<br/>
> 6、启动客户端使用数据<br/>
	
	
