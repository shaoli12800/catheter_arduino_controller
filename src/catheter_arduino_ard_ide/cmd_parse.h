/* encodes responses for the catheter controller */

/* **************** */
/* command parsing functions */
/* **************** */

bool cmd_check(const uint8_t *charBuffer, uint8_t bufferLength, uint8_t* packetIndex, uint8_t* cmdCount)
{
    packetIndex[0] = (charBuffer[0] >> 4) & 7;
    if( charBuffer[0] >> 7 == 0) 
    {
        return false; 
    }
  	cmdCount[0] = charBuffer[0] & 15;
    if( (cmdCount[0]*CMD_LEN + PRE_LEN + POST_LEN + PCK_CHK_LEN)  != bufferLength ) return false;
    uint8_t rearIndex = (charBuffer[bufferLength-2] >> 5) & 7;
    if (rearIndex != packetIndex[0]) return false;
    uint8_t checksum = fletcher8(bufferLength-1, charBuffer);
    if( checksum != charBuffer[bufferLength-1]) return false;
    else return true;
}

/* execute a channel command */
// execute a channel command 
// cmdBytes: the byte array containing the command information
// packetIndex: the identifier of the packet from which this command came
// *reply: the byte array to write reply bytes into
// reply_index: where in the reply array to start writing reply bytes
// *nbytes: return the number of reply bytes appended to the array 
int executeSingleCmd(const uint8_t* cmdBytes, uint8_t *responseBytes, uint8_t *responseIndex, uint8_t  *pollCount)
{
  uint8_t addr = cmdBytes[0] >> 4;
  uint8_t cmdVal = cmdBytes[0] & 15;
  uint16_t cmdData = (((uint16_t)(cmdBytes[1])) << 6) + (cmdBytes[2]);
  
  if( addr == 0)
  {
    // note that i is index from 1 - NCHANNELS (offset by 1)...
    for (uint8_t i(0); i < (NCHANNELS); i++)
    {
      *pollCount += processSingleChannel(i, cmdVal, cmdData, responseBytes, responseIndex);
    } //  for (uint8_t i(0); i < (NCHANNELS); i++)
	  return NCHANNELS;
  } // if (addr == 0)
  else
  {
    int i(addr-1);
    *pollCount += processSingleChannel(i, cmdVal, cmdData, responseBytes, responseIndex);
    return 1;
  } // if (addr == 0) else
  return 0;  //error...
}

// This function parses the command
int cmd_parse(const uint8_t* charBuffer, uint8_t bufferLength, uint8_t cmdCount, uint8_t* outputBytes, uint8_t packetIndex)
{
  uint8_t outputIndex(2); // The first 2 bytes are reserved.
  uint8_t pollCount(0);
  uint8_t responses(0);  
  for (int i = 0; i<cmdCount; i++)
  {
	  const uint8_t* localAddress = charBuffer+PRE_LEN+i*CMD_LEN;
      // execute the channel command
      responses += executeSingleCmd(localAddress, outputBytes, &outputIndex, &pollCount);
  }
  // finish encoding the response...
  outputBytes[0] = 128 + 64 + (packetIndex & 15);   // 1st preamble (ok and packet index)
  outputBytes[1] = (responses << 4) + (pollCount & 15); // 2nd preamble (There could be some overflow here).
  outputBytes[outputIndex] = fletcher8(outputIndex, outputBytes);
  outputIndex++;
  return outputIndex;
}


/* return the (4 bit) command value associated with a particular state */
uint8_t compactCmdVal(int poll, int en, int update, int dir) {
  unsigned int cmd = 0;
  if (poll)   cmd |= (1 << POL_B);
  if (en)     cmd |= (1 << ENA_B);
  if (update) cmd |= (1 << UPD_B);
  if (dir)    cmd |= (1 << DIR_B);
  return cmd;
}

/* return the state associated with a particular (4 bit) command value */
void expandCmdVal(uint8_t cmdVal, int * poll, int * en, int * update, int * dir) {
  *poll = (cmdVal >> POL_B) & 1;
  *en = (cmdVal >> ENA_B) & 1;
  *update = (cmdVal >> UPD_B) & 1;
  *dir = (cmdVal >> DIR_B) & 1;
}




