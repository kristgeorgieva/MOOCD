#include <ctype.h>
#include <stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// A variable that holds all of the color names
char* colorNames[] = {"red", "green", "blue", "black"};

// A variable that holds the amount of ink in each of the heads
float headCurrentInk[4] = {200.0,200.0,200.0,200.0};

/*
 * Function:  GetStringInput
 * --------------------
 * Reads the input and save it into a char array
 *
 *  inputContainer: a char array that will hold the input value
 *
 *  message: the message that will be presented to the user explaining what to type in
 */
void GetStringInput(char inputContainer[20], char* message);

/*
 * Function:  GetIntInput
 * --------------------
 * Reads the input and save it into an intiger variable
 *
 *  inputContainer: an intiger variable that will hold the input value
 *
 *  message: the message that will be presented to the user explaining what to type in
 */
void GetIntInput(int* inputContainer, char* message);

/*
 * Function:  GetFloatInput
 * --------------------
 * Reads the input and save it into a float variable
 *
 *  inputContainer: a float variable that will hold the input value
 *
 *  message: the message that will be presented to the user explaining what to type in
 */
void GetFloatInput(float* inputContainer, char* message);

/*
 * Function:  GetBoolInput
 * --------------------
 * Reads the input and save it into a boolean variable
 *
 *  inputContainer: a boolean variable that will hold the input value
 *
 *  message: the message that will be presented to the user explaining what to type in
 */
void GetBoolInput(bool* inputContainer, char* message);

/*
 * Function:  StringToLower
 * --------------------
 * Converts a string to lower case
 *
 *  input: the string that will be converted
 *
 *  retuns: the string converted to lower case
 */
char* StringToLower(char* input);

/*
 * Function:  StringToUpper
 * --------------------
 * Converts a string to upper case
 *
 *  input: the string that will be converted
 *
 *  retuns: the string converted to upper case
 */
char* StringToUpper(char* input);

/*
 * Function:  Refill
 * --------------------
 * Refills a certain head of the printer
 *
 *  a_headIndex: the index of the head that will be refilled
 */
void Refill(int a_headIndex);

/*
 * Function:  PrintHeads
 * --------------------
 * Prints how much ink there is left in each of the printer heads
 */
void PrintHeads();

/*
 * Function:  PrintPaper
 * --------------------
 * Prints out a paper
 *
 * a_paperCoefficient: a float variable based on the roughness of the paper
 * a_inkIntensity: a float variable based on the intensity of the ink
 * a_imageCoefficient: a float variable based on the presence or absence of an image in the paper
 * a_colorRatio: an array with the ratio of the colors used for printing the paper
 */
void PrintPaper(float a_paperCoefficient, float a_inkIntensity, float a_imageCoefficient, float a_colorRatio[]);


int main()
{

    // Declare a variable that will hold the current command
    char command[20];

	while(1)
	{
	    // Get the command from the input
	    GetStringInput(command,"COMAND[PRINT/REFILL/EXIT]:");

	    // Check if the command is to exit the application
		if (strcmp(StringToLower(command), "exit") == 0)
		{
			return 0;
		}
		// Check if the command is to print
		else if(strcmp(StringToLower(command), "print") == 0)
        {
            // Declare a variable that will hold if image is colored

            bool shouldUseColor;

            // Get if image is colored from inpit
            GetBoolInput(&shouldUseColor, "IS IT COLORED?[Y/N]:");

            // Declare a variable that will hold the number of colors used for the image;
            int numberOfColors;
            // Declare a variable that will hold the percentages of each of the colors used in the image
            float colorPercentages[4] = {0,0,0,0};

            // Check if the image is not colored
            if(shouldUseColor == false)
            {
                colorPercentages[3] = 1;
                numberOfColors = 4;
            }
            // Check if the image is colored
            else
            {
                // Get the number of the colors from the input
                GetIntInput(&numberOfColors, "ENTER NUMBER OF COLORS:");

                if(numberOfColors < 1 || numberOfColors > 4)
                {
                    do
                    {
                        printf("THE NUMBER OF COLORS HAS TO BE BETWEEN 1 AND 4!\n");
                        GetIntInput(&numberOfColors, "ENTER NUMBER OF COLORS:");
                    }
                    while(numberOfColors < 1 || numberOfColors > 4);
                }

                // Declare a variable that will hold the current sum of the percentages
                float sumOfPercentage = 0;

                // Declare a variable that will hold the message for color percentage input
                char message[30];

                int selectedColorIndex;
                char selectedColorName[20];

                // Make the user repeat the input until the input is correct
                do
                {
                    sumOfPercentage = 0;

                    char* colorSelectMessage;

                    // Make variables to store the data about color selection
                    bool isPercentageValid = false;
                    bool isColorValid = false;
                    bool isColorNotUsed = false;

                    // Loop through the number of colors - 1
                    for(int i=0;i<numberOfColors;i++)
                    {
                        // Make the message for the user to select a color
                        sprintf(message,"SELECT COLOR %d![RED/BLUE/GREEN/BLACK]:",i+1);

                        do
                        {
                            // Get the user input
                            GetStringInput(selectedColorName, message);

                            // Check which color he has selected
                            for(int j = 0; j < 4; j++)
                            {
                                if(strcmp(StringToLower(selectedColorName), colorNames[j]) == 0)
                                {
                                    selectedColorIndex = j;
                                    isColorValid = true;
                                    break;
                                }
                            }

                            // Check if the color is valid
                            if(isColorValid == true)
                            {
                                // Check if the color is used
                                if(colorPercentages[selectedColorIndex] == 0)
                                {
                                    isColorNotUsed = true;
                                }
                                else
                                {
                                    printf("THIS COLOR IS ALREADY SELECTED!\n");

                                    isColorNotUsed = false;
                                    isColorValid = false;
                                }
                            }
                            else
                            {
                                printf("INVALID INPUT!\n");

                                isColorNotUsed = false;
                                isColorValid = false;

                            }

                        }
                        while(isColorValid == false || isColorNotUsed == false);

                        // Do not get the user input for the last color percentage because we will calculate it
                        if(i < numberOfColors-1)
                        {
                            do
                            {
                                // Set the message for the color percentage input
                                sprintf(message,"%s COLOR PERCENTAGE: ", StringToUpper(selectedColorName));

                                // Get the color percentage for the current color
                                GetFloatInput(&colorPercentages[selectedColorIndex], message);

                                if(colorPercentages[selectedColorIndex] <= 0 || colorPercentages[selectedColorIndex] >= 100-sumOfPercentage)
                                {
                                    printf("CURRENT COLOR PERCENTAGE HAS TO BE A NUMBER BETWEEN 0 AND %f !\n", 100-sumOfPercentage);
                                }
                            }
                            while(colorPercentages[selectedColorIndex] <= 0 || colorPercentages[selectedColorIndex] >= 100-sumOfPercentage);

                            //Add the current color percentage to the sum
                            sumOfPercentage+= colorPercentages[selectedColorIndex];
                        }
                    }

                    if(sumOfPercentage > 100)
                    {
                        // Display an error if the percentages are more than 100
                        printf("THE TOTAL PERCENTAGE IS MORE THAN OR EQUAL TO 100! ENTER THE PERECNTAGES AGAIN!\n");
                    }
                }
                while(sumOfPercentage > 100);

                // Calculate the last color percentage
                colorPercentages[selectedColorIndex] = 100-sumOfPercentage;

                // Display the last color percentage
                printf("%s PERCENTAGE IS %f\n", StringToUpper(selectedColorName), colorPercentages[selectedColorIndex]);

                // Transform the percentages so that we can use them as multipliers
                for(int i=0;i<4;i++)
                {
                    colorPercentages[i]/=100;
                }

            }


            // Create a variable that will hold the type of the paper
            char paperType[10];

            // Create a variable that will hold if the input is valid
            bool isTypeCorrect = false;

            // Create a variable that will hold the coefficient based on the paper type
            float paperTypeCoefficient=0;

            // Loop until the input is valid
            do
            {
                // Get the input from the user
                GetStringInput(paperType, "ENTER THE TYPE OF THE PAPER?[SMOOTH/NORMAL/ROUGH]: ");

                // Check if input the user entered is smooth (case insensitive)
                if(strcmp(StringToLower(paperType),"smooth") == 0)
                {
                    paperTypeCoefficient = 0.9;
                    isTypeCorrect = true;
                }
                // Check if input the user entered is normal (case insensitive)
                else if(strcmp(StringToLower(paperType),"normal") == 0)
                {
                    paperTypeCoefficient = 1.0;
                    isTypeCorrect = true;
                }
                // Check if input the user entered is rough (case insensitive)
                else if(strcmp(StringToLower(paperType),"rough") == 0)
                {
                    paperTypeCoefficient = 1.15;
                    isTypeCorrect = true;
                }

                // Check if the input valid and display an error if it is not
                if(isTypeCorrect == false)
                {
                    printf("WRONG TYPE! TRY AGAIN!\n");
                }
            }
            while(isTypeCorrect == false);


            // Create a variable that will hold the ink intensity
            float inkIntensity;

            // Loop until the user enters a valid input
            do
            {
                // Get the user input
                GetFloatInput(&inkIntensity, "ENTER THE INK INTENSITY?[BETWEEN 70 AND 120]: ");

                //Check if the input is valid
                if(inkIntensity <70 || inkIntensity > 120)
                {
                    printf("INK INTENSITY HAS TO BE A NUMBER BETWEEN 70 AND 120!\n");
                }

            }
            while(inkIntensity <70 || inkIntensity > 120);

            // Transform the ink intensity so that it can be used as a multyplier
            inkIntensity /=100;

            // Create a variable that will hold if the paper has an image on it
            bool hasImage;

            // Get the input from the user
            GetBoolInput(&hasImage, "DOES IT CONTAIN AN IMAGE?[Y/N]: ");

            // Create a variable that will hold the image coefficient
            float imageCoefficient;

            // Check if the paper has an image
            if(hasImage)
            {
                imageCoefficient = 1.35;
            }
            else
            {
                imageCoefficient = 1.0;
            }

            // Print the paper
            PrintPaper(paperTypeCoefficient,inkIntensity,imageCoefficient,colorPercentages);


        }
        //Check if the command the user eneter is "refill"
        else if(strcmp(StringToLower(command), "refill") == 0)
        {
            char refilColor[20];
            // Create a variable that will hold the index of the head for refill
            int indexOfInkCartrage;

            bool isInputValid = false;

            // Loop until the input is valid
            do
            {
                // Get the user inpit
                GetStringInput(refilColor, "SELECT A COLOR FOR REFILL![RED/GREEN/BLUE/BLACK]: ");
                // Check if the input is correct
                for(int i=0;i<4;i++)
                {
                    if(strcmp(StringToLower(refilColor), colorNames[i])==0)
                    {
                        isInputValid = true;
                        indexOfInkCartrage = i;
                    }
                }
            }
            while(isInputValid == false);

            // Refill the selected head
            Refill(indexOfInkCartrage);

            // Display the amount of ink in all of the heads
            PrintHeads();
        }
        // Print that the command is invalid
        else
        {
            printf("INVALID COMMAND!\n");
        }
	}

	return 0;
}

void GetStringInput(char inputContainer[20], char* message)
{
    // Display a message to the user so that he knows what to enter
    printf(message);

    // Read the input that the user has entered
    scanf("%[^\n]%*c", inputContainer);

    // Flush the input in case the user entered empty or invalid string
    fflush(stdin);
}

void GetIntInput(int* inputContainer, char* message)
{
    // Make a variable that will hold the input of the user as a string
    char inputContainerAsString[20];

    // Get the input of the user and save it in the variable
    GetStringInput(inputContainerAsString, message);

    // Convert the string variable to an int and save it
    *inputContainer = atoi(inputContainerAsString);
}

void GetFloatInput(float* inputContainer, char* message)
{
    // Make a variable that will hold the input of the user as a string
    char inputContainerAsString[20];

    // Get the input of the user and save it in the variable
    GetStringInput(inputContainerAsString, message);

    // Convert the string variable to a float and save it
    *inputContainer = atof(inputContainerAsString);
}

void GetBoolInput(bool* inputContainer, char* message)
{
    // Make a variable that will hold the input of the user as a string
    char inputContainerAsString[20];

    // Get the input of the user and save it in the variable
    GetStringInput(inputContainerAsString, message);

    // Check if the user has entered "Y" (case insensitive) and if so, assign true to the variable
    if(strcmp(StringToLower(inputContainerAsString),"y") == 0)
    {
        *inputContainer = true;
        return;
    }

    // Check if the user has entered "N" (case insensitive) and if so, assign false to the variable
    if(strcmp(StringToLower(inputContainerAsString),"n") == 0)
    {
        *inputContainer = false;
        return;
    }

    // Make the user enter a new input that satisfies the conditions
    do
    {
        printf("INVALID INPUT! TRY AGAIN!\n");

        // Get the input of the user and save it in the variable
        GetStringInput(inputContainerAsString, message);

        // Check if the user has entered "Y" (case insensitive) and if so, assign true to the variable
        if(strcmp(StringToLower(inputContainerAsString),"y") == 0)
        {
            *inputContainer = true;
            return;
        }

        // Check if the user has entered "N" (case insensitive) and if so, assign false to the variable
        if(strcmp(StringToLower(inputContainerAsString),"n") == 0)
        {
            *inputContainer = false;
            return;
        }
    }
    while(1);
}


char* StringToLower(char* input)
{
    // Loop over all of the characters in the string
    for(int i=0;i<=strlen(input);i++)
    {
        // Change each character to lower case
        input[i] = tolower(input[i]);
    }

    // Return the transformed string
    return input;
}

char* StringToUpper(char* input)
{
    // Loop over all of the characters in the string
    for(int i=0;i<=strlen(input);i++)
    {
        // Change each character to upper case
        input[i] = toupper(input[i]);
    }

    // Return the transformed string
    return input;
}

// Function that refills a head
void Refill(int a_headIndex)
{
    // Refill the head at the given index
	headCurrentInk[a_headIndex] = 200;

	// Get the char* into a char[] so that we can call the to upper function
	char colorName[20] = "";
	for(int i=0;i<strlen(colorNames[a_headIndex]);i++)
    {
        colorName[i] = colorNames[a_headIndex][i];
    }
	// Display that the head is refilled
	printf("CARTRAGE %s IS REFILLED!\n", StringToUpper(colorName));
}

void PrintHeads()
{
    // Loop over all of the heads
    for (int index = 0; index < 4; index++)
	{
	    char colorName[20] = "";
        for(int i=0;i<strlen(colorNames[index]);i++)
        {
            colorName[i] = colorNames[index][i];
        }
	    // Display how much ink does each of the heads have
		printf("HEAD %s HAS %f GRAMS OF INk LEFT!\n", StringToUpper(colorName), headCurrentInk[index]);
	}
}

void PrintPaper(float a_paperCoefficient, float a_inkIntensity, float a_imageCoefficient, float a_colorRatio[])
{
    // Calculate the ink coefficient using the parameters
	float requiredInk = a_paperCoefficient * a_inkIntensity * a_imageCoefficient;
	// Create an array that will hold how much ink will each head have to use
	float currentColorNeeded[4];

	// Loop over all of the colors we are going to use
	for (int index = 0; index < 4; index++)
	{
	    // Calculate the current ink needed
		currentColorNeeded[index] = requiredInk * a_colorRatio[index];

		// Check if the head has enough ink
		if (headCurrentInk[index] <= currentColorNeeded[index])
		{
		    char colorName[20] = "";
            for(int i=0;i<strlen(colorNames[index]);i++)
            {
                colorName[i] = colorNames[index][i];
            }
		    // If it does not print an error message and exit the function
			printf("ERROR! %s CARTRAGE NEEDS A REFIL!\n", StringToUpper(colorName));
			return;
		}
	}

	// Loop over all of the colors we used and subtract the ink needed for printing
	for (int index = 0; index < 4; index++)
	{
		headCurrentInk[index] -= currentColorNeeded[index];
	}

	// Display that the paper is printed
	printf("PAGE PRINTED\n");

	// Display how much ink do each of the heads have
    PrintHeads();
}


