#pragma once

void tempInit() {}

void updateTemps();

boolean tsReady();

boolean validAddr(byte* addr);

//This function search for an address that is not currently assigned!
void getDSAddr(byte addrRet[8]);

//Returns Int representing hundreths of degree
int read_temp(byte* addr);

