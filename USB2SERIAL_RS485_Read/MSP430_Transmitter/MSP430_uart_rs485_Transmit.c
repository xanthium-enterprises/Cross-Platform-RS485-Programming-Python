  //----------------------------------------------------------------------------------------------------//
  // RS485 (Transmitter side)                                                                           //
  //----------------------------------------------------------------------------------------------------//
  // Program to send data from MSP430 to PC through RS485 link.MSP430G2553 is interfaced with a RS485   //  
  // decoder chip (MAX485).MSP430 sends a character to PC which is read by the PC side software.        //                                              
  // MSP430 sends a character 'A' .                                                                     //
  //----------------------------------------------------------------------------------------------------//
  //                                                                                                    //
  //  |------------|                                                                                    //
  //  | RS485      |                                               +---------+     +-----------+        //
  //  | Read.exe   |             USB2SERIAL V1.0                   |       RO|---->|P1.1(RXD)  |        //
  //  |------------|            |--------------|                   |      ~RE|-----|P2.1       |        //
  //   \ [][][][][] \===========| USB <- RS485 |~~~~~~~~~~~~~~~~~~~|A,B      |     |           |        //
  //    \------------\   USB    |--------------|      Twisted      |       DE|-----|P2.0       |        //
  //        Laptop                                     Pair        |	   DI|<----|P1.2(TXD)  |        //
  //                                                               +---------+     +-----------+        //
  //                              			              MAX485        MSP430G2553         //
  //                                                                                                    //
  //      [Reciever] <-------------------------------------------- [-------Transmitter---------]        //
  //                                                                                                    //
  //====================================================================================================//
  // Hardware                                                                                           //                                                                                 
  //                                                                                                    //
  // MSP430G2553 on LaunchPad Development board Connected to MAX485.                                    //
  // Clocks   :- DC0 @ 1MHz ,SMCLK @1MHz                                                                //
  // Baudrate :- 9600bps                                                                                //
  //    [MSP430] P1.1(RXD) <- R0 [RS485](Recieve Out)                                                   //
  //    [MSP430] P1.2(TXD) -> DI [RS485](Driver Input)                                                  //
  //    [MSP430] P2.0      -> DE [RS485](Driver Out Enable)                                             //
  //    [MSP430] P2.1      -> RE [RS485](Recieve Enable)                                                //
  //----------------------------------------------------------------------------------------------------//
  // Compiled on IAR Embedded Workbench for MSP430 version 5.30.1                                       //
  // 02-October-2014                                                                                    //
  // Rahul.S                                                                                            //
  //----------------------------------------------------------------------------------------------------//

  /*====================================================================================================*/
  /* www.xanthium.in										                                            */
  /* Copyright (C) 2014 Rahul.S                                                                         */
  /*====================================================================================================*/

    #include "msp430g2553.h"
    void main(void)
    {
      WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog
     
      //------------------- Configure the Clocks -------------------//
        
      if (CALBC1_1MHZ==0xFF)   // If calibration constant erased
         {	
            while(1);          // do not load, trap CPU!!
         } 

      DCOCTL  = 0;             // Select lowest DCOx and MODx settings
      BCSCTL1 = CALBC1_1MHZ;   // Set range
      DCOCTL  = CALDCO_1MHZ;   // Set DCO step + modulation 
      
      
       
      //------------------- Configure the Ports  -------------------//
      
      // Setting the UART function for P1.1 & P1.2
      P1SEL  |=  BIT1 + BIT2;  		// P1.1 UCA0RXD input
      P1SEL2 |=  BIT1 + BIT2;  		// P1.2 UCA0TXD output
      
      // Setting the direction for P1.0, P1.6, P2.0 and P2.1
      P1DIR  |=  BIT0 + BIT6 ;   	// P1.0,P1.6 output(leds)
      P2DIR  |=  BIT0 + BIT1;           // P2.0 -> DE,P2.1 -> ~RE Output
      P1OUT  &= ~BIT0 + BIT6;           // Clear P1.0
      
      //Enabling MAX485 in Transmit mode
      P2OUT  |= BIT0; //P2.0 -> DE (high)
      P2OUT  |= BIT1; //P2.1 -> ~RE (high) RE is active Low 
      
      
      
      //-------------- Configure USCI_A0 in UART mode --------------//  
      
      UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
      UCA0BR0   =  104;                 //  104 From datasheet table-  
      UCA0BR1   =  0;                   // -selects baudrate =9600,clk = SMCLK
      UCA0MCTL  =  UCBRS_1;             // Modulation value = 1 from datasheet
      
      UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0
      
      UCA0TXBUF = 'A';    
      
      _BIS_SR(LPM0_bits + GIE);        // Going to LPM0
        
     }//end of main()

    