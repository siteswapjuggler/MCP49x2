// MCP4902/4912/4922 library for Arduino
// initial release by Sylvain GARNAVAULT - 2016/06/30

#ifndef MCP49x2_h

	#define MCP49x2_h
	
	#include "Arduino.h"         // include arduino Core
    #include "SPI.h"             // include SPI Library

	#define DAC  0x8000          // DACa or DACb selection bit (1 = DACb, 0 = DACa)
	#define BUF  0x4000          // Vref Input Buffer Control bit (1 = Buffered, 0 = Unbuffered)
	#define GA   0x2000          // Output Gain Selection bit (1 = x1, 0 = x2
    #define SDN  0x1000          // Output Shutdown (1 = active, 0 = shutdowm & connected to 500 kOhms)

    #define MCP_4922  0x00       // 12 bits version of the chipset
    #define MCP_4912  0x02       // 10 bits version of the chipset
    #define MCP_4902  0x04       //  8 bits version of the chipset

    #define MCP_49x2_DFT_CS   10  // default CS pin
    #define MCP_49x2_DFT_LDAC  9  // default LDAC pin

	class MCP49x2 {
		public:
            MCP49x2();                                          // initiate chipset
            MCP49x2(byte cs, byte ldac);                        // initiate chipset
            MCP49x2(byte cs, byte ldac, byte chipset);          // initiate chipset
            void trigger();                                     // trig. DAC data to Vout
            void openLatch();                                   // free latch triggering
            void DACA(int value);                               // write DACA value
            void DACB(int value);                               // write DACB value
            void analogWrite(byte dac, int value);              // write DACA/DACB value
            void writeCommandRegister(int value, int config);   // write command register
        
		protected:
            byte _cs;                                           // chip select pin
            byte _ldac;                                         // latch synchronisation pin
            byte _chipset;                                      // chipset version (0 = MPC4922, 2 = MCP4912, 4 = MCP4902);
            void _begin();                                      // beginning SPI transaction
            void _end();                                        // endinf SPI transaction
	};

    class MCP4922 : public MCP49x2 {
        public:
            MCP4922() : MCP49x2(MCP_49x2_DFT_CS, MCP_49x2_DFT_LDAC, MCP_4922) {};
            MCP4922(byte cs, byte ldac) : MCP49x2(cs, ldac, MCP_4922) {};
    };

    class MCP4912 : public MCP49x2 {
        public:
            MCP4912() : MCP49x2(MCP_49x2_DFT_CS, MCP_49x2_DFT_LDAC, MCP_4912) {};
            MCP4912(byte cs, byte ldac) : MCP49x2(cs, ldac, MCP_4912) {};
    };

    class MCP4902 : public MCP49x2 {
        public:
            MCP4902() : MCP49x2(MCP_49x2_DFT_CS, MCP_49x2_DFT_LDAC, MCP_4902) {};
            MCP4902(byte cs, byte ldac) : MCP49x2(cs, ldac, MCP_4902) {};
    };

#endif // MCPMCP49x2_h
