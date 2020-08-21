package main

import (
	"fmt"
	define "gorm/gorm"
)

func GetByNonPrimaryKey() bool {
	request, ret := gormSvr.GetRequestForGetByNonPrimaryKey("account")
	if request == nil || ret != define.GORM_CODE_OK {
		fmt.Println("get insert request for account failed.")
		return false
	}

	record, ret := request.AddRecord()
	if record == nil || ret != define.GORM_CODE_OK {
		fmt.Println("add record for request failed.")
		return false
	}

	if ret := record.SetFieldIntValue("id", 0); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}

	uCBID, errCode := gormSvr.SendRequest(request)
	if errCode != define.GORM_CODE_OK {
		fmt.Println("send request to gorm failed")
		return false
	}
	fmt.Println("send request to gorm success, call back id is:", uCBID)
	return true
}
