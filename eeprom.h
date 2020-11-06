void EEPROM_write(unsigned int Address, unsigned char Data)
{

	while(EECR & (1<<EEWE));
	/* Set up address and Data Registers */
	EEAR = Address;
	EEDR = Data;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEWE);

}

/******** EEPROM DATA READING *********/


unsigned char EEPROM_read(unsigned int Address)
{

	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address register */
	EEAR = Address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;

}