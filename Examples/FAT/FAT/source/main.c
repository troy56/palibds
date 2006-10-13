/* This shows how to use the basic PAFS functions ! PAFS is a file system for nintendo DS, which supports multiple files in multiple directories... See the PAFSFolders to see how to detect the different folders

*/

// Includes
#include <PA9.h>       // Include for PA_Lib
#include <stdio.h>
#include <stdlib.h>

char filename[50]; // Temporary string for file names


char* GetTextFromKeyboard();

// Function: main()
int main(int argc, char ** argv)
{
	PA_Init();    // Initializes PA_Lib
	PA_InitVBL(); // Initializes a standard VBL
	
	PA_InitText(0, 0);  // Initialise the text system on the bottom screen	
	
	PA_InitText(1, 0);  // Initialise the text system on the top screen
	
	PA_WaitForVBL();  PA_WaitForVBL();  PA_WaitForVBL();  // wait a few VBLs
	
	if (PA_InitFat()) {
    
		PA_OutputText(1,0,0,"fat init success");					//yey we have a compatible fat card!
		PA_OutputText(1,0,1,PA_ReadTextFile("/test.txt"));			// Lets read a text file located at /test.txt
		
		// lets write the output from the keyboard to /test.txt and print out the amount of bytes written to disk	
		PA_OutputText(1,0,0,"%d  bytes written", PA_WriteTextFile("/test.txt",GetTextFromKeyboard()));	
	
	} else {
	
		PA_OutputText(1,0,0,"fat init failure");
   
					// Failed to find a compatible card, stop program
		while(1) {

		}
	} 
	
	PA_KeyboardOut();
	PA_OutputText(1,0,4,"File written to card, Reboot ds and check the message");

	while (1)
	{ 
			//end
		PA_WaitForVBL();
	}
	
	return 0;
} // End of main()
	

char* GetTextFromKeyboard() {

	char* text2write=" ";
	char text[200];
	
	PA_InitKeyboard(2); // Load the keyboard on background 2...
	PA_KeyboardIn(20, 100); // This scrolls the keyboard from the bottom, until it's at the right position
	// PA_KeyboardOut() can be used to scroll the Keyboard out
	// PA_ScrollKeyboardXY(x, y) can be used to set the keyboards position
	
	
	PA_OutputSimpleText(1, 7, 10, "Text : "); 
	
	s32 nletter = 0; // Next letter to right. 0 since no letters are there yet
	char letter = 0; // New letter to write.

	// Infinite loop to keep the program running
	while (1)
	{

		letter = PA_CheckKeyboard();

		if (letter > 31) { // there is a new letter

			text[nletter] = letter;
			nletter++;
		}

		else if ((letter == PA_BACKSPACE)&&nletter) { // Backspace pressed

			nletter--;
			text[nletter] = ' '; // Erase the last letter
		}

		else if (letter == '\n'){ // Enter pressed

			text[nletter] = letter;
			nletter++;
			strcpy(text2write,text);
			PA_OutputSimpleText(1, 8, 14, "writing text :" );
			PA_OutputSimpleText(1, 8, 15, text2write ); // text Thats going to be written
			return text2write;							 //return that text
		}

		PA_OutputSimpleText(1, 8, 11, text); // Display the typed characters
		PA_WaitForVBL();
	}

return 0;
}
