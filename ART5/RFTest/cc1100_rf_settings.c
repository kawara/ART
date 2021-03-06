/*****************************************************************************
 * RF Test Settings sanity check
 * 
 * Copyright 2011 Ricky Ng-Adam
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#ifndef ARDUINO
#include <stdio.h>
#include <math.h>

#include "cc1100_rf_settings.h"

settings_t rfSettingsDefaults = {
    0x29,  // IOCFG2              GDO2 Output Pin Configuration
    0x2e,  // IOCFG1              GDO1 Output Pin Configuration
    0x3f,  // IOCFG0              GDO0 Output Pin Configuration
    0x07,  // FIFOTHR             RX FIFO and TX FIFO Thresholds
    0xD3,  // SYNC1               Sync Word, High Byte
    0x91,  // SYNC0               Sync Word, Low Byte
    0xff,  // PKTLEN              Packet Length
    0x04,  // PKTCTRL1            Packet Automation Control
    0x45,  // PKTCTRL0            Packet Automation Control
    0x00,  // ADDR                Device Address
    0x00,  // CHANNR              Channel Number
    0x0F,  // FSCTRL1             Frequency Synthesizer Control
    0x00,  // FSCTRL0             Frequency Synthesizer Control
    0x1E,  // FREQ2               Frequency Control Word, High Byte
    0xc4,  // FREQ1               Frequency Control Word, Middle Byte
    0xec,  // FREQ0               Frequency Control Word, Low Byte
    0x8c,  // MDMCFG4             Modem Configuration
    0x22,  // MDMCFG3             Modem Configuration
    0x02,  // MDMCFG2             Modem Configuration
    0x22,  // MDMCFG1             Modem Configuration
    0xf8,  // MDMCFG0             Modem Configuration
    0x47,  // DEVIATN             Modem Deviation Setting
    0x07,  // MCSM2               Main Radio Control State Machine Configuration
    0x30,   // MCSM1               Main Radio Control State Machine Configuration
    0x04,  // MCSM0               Main Radio Control State Machine Configuration
    0x36,  // FOCCFG              Frequency Offset Compensation Configuration
    0x6c,  // BSCFG               Bit Synchronization Configuration
    0x03,  // AGCCTRL2            AGC Control
    0x40,  // AGCCTRL1            AGC Control
    0x91,  // AGCCTRL0            AGC Control
    0x87,  // WOREVT1             High Byte Event0 Timeout
    0x6b,  // WOREVT0             Low Byte Event0 Timeout
    0xf8,  // WORCTRL             Wake On Radio Control
    0x56,  // FREND1              Front End RX Configuration
    0x10,  // FREND0              Front End TX Configuration
    0xa9,  // FSCAL3              Frequency Synthesizer Calibration
    0x0a,  // FSCAL2              Frequency Synthesizer Calibration
    0x20,  // FSCAL1              Frequency Synthesizer Calibration
    0x0d,  // FSCAL0              Frequency Synthesizer Calibration
    0x41,  // RCCTRL1             RC Oscillator Configuration
    0x00,  // RCCTRL0             RC Oscillator Configuration
    0x59,  // FSTEST              Frequency Synthesizer Calibration Control
    0x7F,  // PTEST               Production Test
    0x3F,  // AGCTEST             AGC Test
    0x88,  // TEST2               Various Test Settings
    0x31,  // TEST1               Various Test Settings
    0x0B,  // TEST0               Various Test Settings
};

void outputConfig(const settings_t& rfSettings, unsigned int xosc_khz) {
  for(byte i=0;i<3;i++) {
    byte io = 2-i;
    printf("GDO%d ", io);
    // see page 60
    switch(rfSettings.registers[i] & 63) {
      case 0:
        printf("Associated to RX Fifo; above or below threshold");
        break;
      case 1:
        printf("Associated to RX Fifo; threshold or end packet. deasserts empty");
        break;
      case 2:
        printf("Associated to TX Fifo");
        break;
      case 3:
        printf("Associated to TX Fifo overflow");
        break;
      case 4:
        printf("Associated to RX Fifo overflow");
        break;
      case 5:
        printf("Associated to RX fifo underflow");
        break;
      case 6:
        printf("Assert on sync word, deassert on the end of packet");
        break;
      case 7:
        printf("Assert packet received with CRC OK");
        break;
      case 8:
        printf("Preamble quality reached");
        break;
      case 9:
        printf("Clear channel assessment");
        break;
      case 10:
        printf("Lock detector output");
        break;
      case 11:
        printf("Serial clock");
        break;
      case 12:
        printf("Serial synchronous data output");
        break;
      case 13:
        printf("Serial data output, asynchronous serial mode");
        break;
      case 14:
        printf("Carrier sense");
        break;
      case 15:
        printf("CRC_OK");
        break;
      case 22:
        printf("RX_HARD_DATA[1]");
        break;
      case 23:
        printf("RX_HARD_DATA[0]");
        break;
      case 27:
        printf("PA_PD");
        break;
      case 28:
        printf("LNA_PD");
        break;
      case 29:
        printf("RX_SYMBOL_TICK");
        break;
      case 36:
        printf("WOR_EVNT0");
        break;
      case 37:
        printf("WOR_EVNT1");
        break;
      case 39:
        printf("CLK_32K");
        break;
      case 41:
        printf("CHIP_RDYn");
        break;
      case 43:
        printf("XOSC_STABLE");
        break;
      case 45:
        printf("GDO0_Z_EN_N");
        break;
      case 46:
        printf("High impedance (3 state)");
        break;
      case 47:
        printf("HW to 0");
        break;
      case 48:
        printf("CLK_XOSC/1");
        break;
      case 49:
        printf("CLK_XOSC/1.5");
        break;
      case 50:
        printf("CLK_XOSC/2");
        break;
      case 51:
        printf("CLK_XOSC/3");
        break;
      case 52:
        printf("CLK_XOSC/4");
        break;
      case 53:
        printf("CLK_XOSC/6");
        break;
      case 54:
        printf("CLK_XOSC/8");
        break;
      case 55:
        printf("CLK_XOSC/12");
        break;
      case 56:
        printf("CLK_XOSC/16");
        break;
      case 57:
        printf("CLK_XOSC/24");
        break;
      case 58:
        printf("CLK_XOSC/32");
        break;
      case 59:
        printf("CLK_XOSC/48");
        break;
      case 60:
        printf("CLK_XOSC/64");
        break;
      case 61:
        printf("CLK_XOSC/96");
        break;
      case 62:
        printf("CLK_XOSC/128");
        break;
      case 63:
        printf("CLK_XOSC/192");
        break;
      default:
        printf("Reserved for tests");
        break;
    }
    printf("\n");
  }
  printf("GDO0 temperature output = %s\n", rfSettings.values.temp_sensor_enable?"true":"false");
// Base frequency = 433.999969 
// Carrier frequency = 433.999969 
// Channel number = 0 
  printf("Channel number = ");
  printf("%d\n", rfSettings.values.chan);
// Carrier frequency = 433.999969 
// Modulated = true 
// Modulation format = GFSK 
  printf("Modulation format = ");
  switch(rfSettings.values.mod_format) {
    case 0:
      printf("2-FSK\n");
      break;
    case 1:
      printf("GFSK\n");
      break;
    case 3:
      printf("ASK/OOK\n");
      break;
    case 7:
      printf("MSK\n");
      break;
    default:
      printf("None\n");
      break;
      
  }
// Manchester enable = false 
  printf("Manchester enable = %s\n", rfSettings.values.manchester_en?"true":"false");
// Sync word qualifier mode = 30/32 sync word bits detected 
  printf("Sync word qualifier mode = ");
  switch(rfSettings.values.sync_mode) {
    case 0:
      printf("No preamble/sync\n");
      break;
    case 1:
      printf("15/16 sync word bits detected\n");
      break;
    case 2:
      printf("16/16 sync word bits detected\n");
      break;
    case 3:
      printf("30/32 sync word bits detected\n");
      break;
    case 4:
      printf("No preamble/sync, carrier-sense above threshold\n");
      break;
    case 5:
      printf("15/16 + carrier-sense above threshold\n");
      break;
    case 6:
      printf("16/16 + carrier-sense above threshold\n");
      break;
    case 7:
      printf("30/32 + carrier-sense above threshold\n");
      break;
    default:
      printf("Unsupported value!\n");
      break; 
  }
// Preamble count = 4 
  printf("Preamble count = ");
  switch(rfSettings.values.num_preamble) {
    case 0:
      printf("2\n");
      break;
    case 1:
      printf("3\n");
      break;
    case 2:
      printf("4\n");
      break;
    case 3:
      printf("6\n");
      break;
    case 4:
      printf("8\n");
      break;
    case 5:
      printf("12\n");
      break;
    case 6:
      printf("16\n");
      break;
    case 7:
      printf("24\n");
      break;
    default:
      printf("Unsupported value!\n");
      break; 
  }
  // Channel spacing = 199.951172 
  // Carrier frequency = 433.999969
  // see Frequency Programming, page 55
  unsigned int frequency = 0;
  frequency |= rfSettings.values.freq_high<<16 | rfSettings.values.freq_middle<<8 | rfSettings.values.freq_low;
  // see freq2 pg 73
  double frequency_increment = (xosc_khz*1000.0)/pow(2,16);
  printf("Frequency increment %f\n", frequency_increment);
  unsigned long frequency_converted = frequency * frequency_increment;
  printf("Starting frequency %ld hz (from 24-bits registers value %d)\n", frequency_converted, frequency);
  double channel_spacing = ((256 + rfSettings.values.chanspc_m)*(2^(rfSettings.values.chanspc_e-2)));
  printf("Channel spacing = %f hz\n", channel_spacing);
  double carrier = frequency_increment*(frequency + rfSettings.values.chan * channel_spacing);
  printf("Carrier frequency %f hz\n", carrier);
  // see FSCTRL1 page 73
  double preferred_if = ((xosc_khz*1000)/pow(2,10))*rfSettings.values.freq_if;
  printf("Preferred RX frequency delta substraction %f hz\n", preferred_if);
  // see FSCTRL0 page 73
  printf("Frequency synthesizer offset %f hz (freqoff value %d)\n", (xosc_khz*1000/pow(2,14))*rfSettings.values.freqoff, rfSettings.values.freqoff);
  // Data rate = 2.39897 
  // RX filter BW = 58.035714 
  // Data format = Normal mode 
  printf("Data format = ");
  switch(rfSettings.values.pkt_format) {
    case 0:
      printf("Normal mode, use FIFOs for RX and TX\n");
      break;
    case 1:
      printf("Synchronous serial mode.\n");
      break;
    case 2:
      printf("Random TX mode\n");
      break;
    case 3:
      printf("Asynchronous mode\n");
      break;
    default:
      printf("Unsupported value!\n");
      break; 
  }

// Length config = Variable packet length mode. Packet length configured by the first byte after sync word 
  printf("Length config = ");
  switch(rfSettings.values.length_config) {
    case 0:
      printf("Fixed packet length mode.  Length configured in PKTLEN register\n");
      break;
    case 1:
      printf("Variable packet length mode. Length configured by the first byte after sync word\n");
      break;
    case 2:
      printf("Infinite packet length mode\n");
      break;
    case 3:
      printf("Reserved!\n");
      break;
    default:
      printf("Unsupported value!\n");
      break; 
  }
// CRC enable = true 
  printf("CRC enable = %s\n", rfSettings.values.crc_en?"true":"false");
// Packet length = 255 
  printf("Packet length = ");
  printf("%d\n", rfSettings.values.packet_length);
// Device address = 0 
  printf("Device address = ");
  printf("%d\n", rfSettings.values.device_addr);
// Address config = No address check 
  printf("Address config = ");
  switch(rfSettings.values.adr_chk) {
    case 0:
      printf("No address check\n");
      break;
    case 1:
      printf("Address check, no broadcast\n");
      break;
    case 2:
      printf("Address check and 0 (0x00) broadcast\n");
      break;
    case 3:
      printf("Address check and 0 (0x00) and 255 (0xFF) broadcast\n");
      break;
    default:
      printf("Unsupported value!\n");
      break; 
  }
// CRC autoflush = false 
  printf("CRC autoflush = %s\n", rfSettings.values.crc_autoflush?"true":"false");
// PA ramping = false 
// TX power = 0   
}


const char* getRegisterName(int i) {
  switch(i) {
    case 0x00: return "IOCFG2";         
    case 0x01: return "IOCFG1";         
    case 0x02: return "IOCFG0";         
    case 0x03: return "FIFOTHR";         
    case 0x04: return "SYNC1";         
    case 0x05: return "SYNC0";         
    case 0x06: return "PKTLEN";         
    case 0x07: return "PKTCTRL1";         
    case 0x08: return "PKTCTRL0";         
    case 0x09: return "ADDR";         
    case 0x0a: return "CHANNR";         
    case 0x0b: return "FSCTRL1";         
    case 0x0c: return "FSCTRL0";         
    case 0x0d: return "FREQ2";         
    case 0x0e: return "FREQ1";         
    case 0x0f: return "FREQ0";         
    case 0x10: return "MDMCFG4";         
    case 0x11: return "MDMCFG3";         
    case 0x12: return "MDMCFG2";        
    case 0x13: return "MDMCFG1";        
    case 0x14: return "MDMCFG0";       
    case 0x15: return "DEVIATN";       
    case 0x16: return "MCSM2";        
    case 0x17: return "MCSM1";         
    case 0x18: return "MCSM0";        
    case 0x19: return "FOCCFG";         
    case 0x1a: return "BSCFG";        
    case 0x1b: return "AGCCTRL2";        
    case 0x1c: return "AGCCTRL1";         
    case 0x1d: return "AGCCTRL0";        
    case 0x1e: return "WOREVT1";        
    case 0x1f: return "WOREVT0";         
    case 0x20: return "WORCTRL";       
    case 0x21: return "FREND1";       
    case 0x22: return "FREND0";        
    case 0x23: return "FSCAL3";        
    case 0x24: return "FSCAL2";         
    case 0x25: return "FSCAL1";         
    case 0x26: return "FSCAL0";         
    case 0x27: return "RCCTRL1";
    case 0x28: return "RCCTRL0"; 
    case 0x29: return "FSTEST";        // Frequency synthesizer calibration control
    case 0x2A: return "PTEST";        // Production test
    case 0x2B: return "AGCTES";        // AGC test
    case 0x2C: return "TEST2";        // Various test settings
    case 0x2D: return "TEST1";        // Various test settings
    case 0x2E: return "TEST0";        // Various test settings    
  }
}

void compare(const settings_t& rfSettingsA, const settings_t& rfSettingsB) {
  for(int i=0; i<ADDR_TEST0+1; i++) {
    if(rfSettingsA.registers[i] != rfSettingsB.registers[i]) {
      printf("Register %s (%d) differs: %d vs %d\n", getRegisterName(i), i, rfSettingsA.registers[i], rfSettingsB.registers[i]);
    }
  }
}


int main(void) {
   printf("NetUSB------------------------------------\n");
   outputConfig(rfSettings_netusb, 26000);
   printf("RFC1100A example------------------------------------\n");
   outputConfig(rfSettings_rfc1100a, 26000);
   printf("Defaults------------------------------------\n");
   outputConfig(rfSettings_rfc1100a, 26000);
   printf("Comparing RFC1100A and NetUSB------------------------------------\n");
   compare(rfSettings_rfc1100a, rfSettings_netusb);
   make_compatible(rfSettings_rfc1100a, rfSettings_netusb);
   printf("Comparing RFC1100A and NetUSB after conversion------------------------------------\n");
   compare(rfSettings_rfc1100a, rfSettings_netusb);
   printf("Final------------------------------------\n");
   outputConfig(rfSettings_rfc1100a, 26000);

}
#endif
