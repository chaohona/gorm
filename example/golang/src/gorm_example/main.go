package main

import (
	"flag"
	"fmt"
	"glog"
	gorm_client "gorm"
	define "gorm/gorm"
	"time"
)

var gormSvr gorm_client.Server

func RecvGetResult() {

	for {
		response := gormSvr.RecvResponse()
		if response == nil {
			time.Sleep(10 * time.Millisecond)
			continue
		}
		fmt.Println("get response form gorm server")
		retCode := response.GetResultCode()

		retCode.Print()

		for {
			record, errCode := response.GetNextRecord()
			fmt.Println(record)
			fmt.Println(errCode)
			if errCode != define.GORM_CODE_OK {
				fmt.Println("get next record, got err:", errCode)
				break
			}
			if record == nil {
				fmt.Println("recod is nil")
				break
			}
			msg, errCode := record.GetData()
			if errCode != define.GORM_CODE_OK {
				fmt.Println("get record source proto message got err:", errCode)
				break
			}
			if msg == nil {
				fmt.Println("msg is nil")
				break
			}
			id, _ := record.GetFieldIntValue("roleid")
			fmt.Println("roleid:", id)
			roleName, _ := record.GetFieldStrValue("rolename")
			fmt.Println("rolename:", roleName)
			exp, _ := record.GetFieldIntValue("exp")
			fmt.Println("exp:", exp)
			fmt.Println("get non field value, ret code:", retCode)
		}
		break
	}
	return
}

func main() {
	/*var insertReq *define.GORM_PB_INSERT_REQ = &define.GORM_PB_INSERT_REQ{
		Header: &define.GORM_PB_REQ_HEADER{
			TableId:   1,
			FieldMode: "test",
		},
	}
	data, err := proto.Marshal(insertReq)
	_ = data
	fmt.Println("marshal err is:", err)

	var unmarshalResult define.GORM_PB_INSERT_REQ

	var testData []byte = []byte{10, 0, 18, 0, 24, 1}
	err = proto.Unmarshal(testData, &unmarshalResult)
	fmt.Println("unmarshal result is:", unmarshalResult)
	fmt.Println("tableid:", unmarshalResult.Header.TableId, ", fieldMode:", unmarshalResult.Header.FieldMode)
	return*/

	flag.Parse()

	glog.SetLogFile("D:/work/codes/gorm/golang/test/log/gorm_test.log")
	if define.GORM_CODE_OK != gormSvr.Init("192.168.12.42:8806") {
		fmt.Println("init gorm failed.")
		return
	}

	if !gormSvr.Start() {
		fmt.Println("start gorm client failed.")
		return
	}

	for i := 0; i < 10; i++ {
		if !Get() {
			fmt.Println("test get request failed.")
			return
		}

		RecvGetResult()
	}

}
