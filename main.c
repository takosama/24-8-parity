//////////////////////////パリティチェックand訂正プログラム///////////////////////////////////
//rtn 0 ok
//rtn 1 訂正済み
//rtn -1 ng
int  DecodeBCH24_8(uint32_t *data)
{
	uint32_t arr[24] = {
		0x00010000,
		0x00020000,
		0x00040000,
		0x00080000,
		0x00100000,
		0x00200000,
		0x00400000,
		0x00800000,
		0x00000100,
		0x00000200,
		0x00000400,
		0x00000800,
		0x00001000,
		0x00002000,
		0x00004000,
		0x00008000,
		0x00000001,
		0x00000002,
		0x00000004,
		0x00000008,
		0x00000010,
		0x00000020,
		0x00000040,
		0x00000080
	};

	uint32_t h0 = ((*data & arr[0]) ? 1 : 0) ^ ((*data & arr[1]) ? 1 : 0) ^ ((*data & arr[2]) ? 1 : 0) ^ ((*data & arr[3]) ? 1 : 0) ^ ((*data & arr[4]) ? 1 : 0);
	uint32_t h1 = ((*data & arr[5]) ? 1 : 0) ^ ((*data & arr[6]) ? 1 : 0) ^ ((*data & arr[7]) ? 1 : 0) ^ ((*data & arr[8]) ? 1 : 0) ^ ((*data & arr[9]) ? 1 : 0);
	uint32_t h2 = ((*data & arr[10]) ? 1 : 0) ^ ((*data & arr[11]) ? 1 : 0) ^ ((*data & arr[12]) ? 1 : 0) ^ ((*data & arr[13]) ? 1 : 0) ^ ((*data & arr[14]) ? 1 : 0);
	uint32_t h3 = ((*data & arr[15]) ? 1 : 0) ^ ((*data & arr[16]) ? 1 : 0) ^ ((*data & arr[17]) ? 1 : 0) ^ ((*data & arr[18]) ? 1 : 0) ^ ((*data & arr[19]) ? 1 : 0);
	uint32_t h4 = ((*data & arr[0]) ? 1 : 0) ^ ((*data & arr[5]) ? 1 : 0) ^ ((*data & arr[10]) ? 1 : 0) ^ ((*data & arr[15]) ? 1 : 0) ^ ((*data & arr[20]) ? 1 : 0);
	uint32_t h5 = ((*data & arr[1]) ? 1 : 0) ^ ((*data & arr[6]) ? 1 : 0) ^ ((*data & arr[11]) ? 1 : 0) ^ ((*data & arr[16]) ? 1 : 0) ^ ((*data & arr[21]) ? 1 : 0);
	uint32_t h6 = ((*data & arr[2]) ? 1 : 0) ^ ((*data & arr[7]) ? 1 : 0) ^ ((*data & arr[12]) ? 1 : 0) ^ ((*data & arr[17]) ? 1 : 0) ^ ((*data & arr[22]) ? 1 : 0);
	uint32_t h7 = ((*data & arr[3]) ? 1 : 0) ^ ((*data & arr[8]) ? 1 : 0) ^ ((*data & arr[13]) ? 1 : 0) ^ ((*data & arr[18]) ? 1 : 0) ^ ((*data & arr[23]) ? 1 : 0);

	uint32_t h = ((h7 & 0x00000001)) + ((h6 & 0x00000001) << 1) + ((h5 & 0x00000001) << 2) + ((h4& 0x00000001) << 3) + ((h3 & 0x00000001) << 4)+ ((h2 & 0x00000001) << 5)+ ((h1 & 0x00000001) << 6)+ ((h0 & 0x00000001) << 7);
	uint32_t p0 = ((uint8_t*)data)[3];
	uint32_t H0 = h ^ p0;

	if (H0 == 0)
		return 0;

	switch (H0)
	{
	case 0b10000000:
		*data ^= arr[4];
		return 1;
	case 0b01000000:
		*data ^= arr[9];
		return 1;
	case 0b00100000:
		*data ^= arr[14];
		return 1;
	case 0b00010000:
		*data ^= arr[19];
		return 1;
	case 0b00001000:
		*data ^= arr[20];
		return 1;
	case 0b00000100:
		*data ^= arr[21];
		return 1;
	case 0b00000010:
		*data ^= arr[22];
		return 1;
	case 0b00000001:
		*data ^= arr[23];
		return 1;

	case 0b10001000:
		*data ^= arr[0];
		return 1;
	case 0b10000100:
		*data ^= arr[1];
		return 1;
	case 0b10000010:
		*data ^= arr[2];
		return 1;
	case 0b10000001:
		*data ^= arr[3];
		return 1;

	case 0b01001000:
		*data ^= arr[5];
		return 1;
	case 0b01000100:
		*data ^= arr[6];
		return 1;
	case 0b01000010:
		*data ^= arr[7];
		return 1;
	case 0b01000001:
		*data ^= arr[8];
		return 1;

	case 0b00101000:
		*data ^= arr[10];
		return 1;
	case 0b00100100:
		*data ^= arr[11];
		return 1;
	case 0b00100010:
		*data ^= arr[12];
		return 1;
	case 0b00100001:
		*data ^= arr[13];
		return 1;

	case 0b00011000:
		*data ^= arr[15];
		return 1;
	case 0b00010100:
		*data ^= arr[16];
		return 1;
	case 0b00010010:
		*data ^= arr[17];
		return 1;
	case 0b00010001:
		*data ^= arr[18];
		return 1;
	default:
		return -1;
	}
}




///////////////////////////使用側///////////////////////////////////

int16_t cnt=0;
while (1)
  {

	  arr[0] = 0b10100000;
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 0);

	  HAL_SPI_Transmit(&hspi2, arr ,1, 1000);

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);

	  HAL_Delay(1);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 0);

	

	  HAL_SPI_Receive(&hspi2, arr2, 4, 1000);

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);

	 

	 
	  int32_t* tmp= (uint32_t*)arr2;
	  auto ans = DecodeBCH24_8(tmp);
	  if ( ans == 0　|| ans==1)
	  {
		  cnt = (int16_t)((((uint8_t*)(tmp))[1] << 8) + ((uint8_t*)(tmp))[2]);
		 }
	  else
	  {
	 // 訂正不可能
	  }

 	  HAL_Delay(1);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */


  }
  /* USER CODE END 3 */
}
