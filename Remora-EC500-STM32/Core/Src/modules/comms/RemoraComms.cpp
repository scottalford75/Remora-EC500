#include "RemoraComms.h"


RemoraComms::RemoraComms()
{
	printf("Creating an Ethernet communication monitoring module\n");

	this->LED = new Pin("PC_3", OUTPUT);
	this->LED->set(true); //EC500 outputs are inverted
}


void RemoraComms::update()
{
	if (this->data)
	{
		this->noDataCount = 0;
		this->status = true;
		this->LED->set(false);
	}
	else
	{
		this->noDataCount++;
	}

	if (this->noDataCount > DATA_ERR_MAX)
	{
		this->noDataCount = 0;
		this->status = false;
		this->LED->set(true);
	}

	this->data = false;
}



void RemoraComms::dataReceived()
{
	this->data= true;
}


bool RemoraComms::getStatus()
{
	return this->status;
}

