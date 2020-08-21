package main

import (
	"fmt"
	define "gorm/gorm"
)

func Insert() bool {
	request, ret := gormSvr.GetRequestForInsert("role")
	if request == nil || ret != define.GORM_CODE_OK {
		fmt.Println("get insert request for role failed.")
		return false
	}

	record, ret := request.AddRecord()
	if record == nil || ret != define.GORM_CODE_OK {
		fmt.Println("add record for request failed.")
		return false
	}

	if ret := record.SetFieldIntValue("roleId", 200); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}

	if ret := record.SetFieldStrValue("roleName", "roleName"); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldIntValue("level", 1); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldIntValue("exp", 1); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldIntValue("characterId", 1); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldIntValue("gold", 1); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldIntValue("offlineTime", 1); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldIntValue("inited", 1); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldIntValue("createTime", 1); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldStrValue("face", "face_test"); ret != define.GORM_CODE_OK {
		fmt.Println("set value for record failed, code:%d", ret)
		return false
	}
	if ret := record.SetFieldIntValue("online", 1); ret != define.GORM_CODE_OK {
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
