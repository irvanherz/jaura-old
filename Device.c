#include "Types.h"
#include "KFilesystem.h"
#include "Device.h"

DEVICE *DeviceList[MAX_DEVICE];

int DeviceAdd(DEVICE_ID id, DEVICE *device){
	if(MAJOR_OF(id) >= MAX_DEVICE)
		return -1;
	
	if(DeviceList[MAJOR_OF(id)])
		return -2;
	DeviceList[MAJOR_OF(id)] = device;
	return 0;
}

int DeviceDelete(DEVICE_ID id){
	if(MAJOR_OF(id) >= MAX_DEVICE)
		return -1;
	
	if(!DeviceList[MAJOR_OF(id)])
		return -2;
	DeviceList[MAJOR_OF(id)] = 0;
	return 0;
}

DEVICE *DeviceGet(DEVICE_ID id){
	if(MAJOR_OF(id) >= MAX_DEVICE)
		return 0;
	return DeviceList[MAJOR_OF(id)];
}

FNODE_METHOD *DeviceGetMethod(DEVICE_ID id){
	if(MAJOR_OF(id) >= MAX_DEVICE)
		return 0;
	return DeviceList[MAJOR_OF(id)]->method;
}