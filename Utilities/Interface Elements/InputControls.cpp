//  InputControls.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#include "InputControls.hpp"






/**
 * Button
 * Default constructor that initializes a Button object with default values.
 */
Button::Button()
{
	/// Set default values
	label = ""; // Set the button label to an empty string
	rect = ofRectangle(); // Initialize the button rectangle with default values
	isPressed = false; // Set the button state to not pressed
}


/**
 * Button
 * Parameterized constructor that initializes a Button object with specified label, position, and dimensions.
 *
 * @param _label: The label for the button
 * @param _x: The x-coordinate of the button position
 * @param _y: The y-coordinate of the button position
 * @param _w: The width of the button
 * @param _h: The height of the button
 */
Button::Button(std::string _label, float _x, float _y, float _w, float _h)
{
	/// Assign the parameter values to the object
	isPressed = false; // Set the button state
	label = _label; // Set the label of the button
	rect.set(_x, _y, _w, _h); // Set the position and dimensions of the button
}

/**
 * Button
 * Parameterized constructor that initializes a Button object with specified label, position, and dimensions
 * where the Button's isPressed event tied to the defined callback function.
 *
 * @param _label: The label for the button
 * @param _x: The x-coordinate of the button position
 * @param _y: The y-coordinate of the button position
 * @param _w: The width of the button
 * @param _h: The height of the button
 */
Button::Button(std::string _label, float _x, float _y, float _w, float _h, std::function<void()> callback) : onClick(callback) // Set the callback function for the button
{
	/// Assign the parameter values to the object
	isPressed = false; // Set the button state
	label = _label; // Set the label of the button
	rect.set(_x, _y, _w, _h); // Set the position and dimensions of the button
}
//*/


/**
 * Button
 * Parameterized constructor that initializes a Button object with specified label, position, and dimensions
 * where the Button's isPressed event tied to the defined callback function.
 *
 * @param _label: The label for the button
 * @param _x: The x-coordinate of the button position
 * @param _y: The y-coordinate of the button position
 * @param _w: The width of the button
 * @param _h: The height of the button
 *
 Button::Button(std::string _label, float _x, float _y, float _w, float _h, ButtonClickCallback callback) : onClickCallback(callback) // Set the callback function for the button
 {
 /// Assign the parameter values to the object
 isPressed = false; // Set the button state
 label = _label; // Set the label of the button
 rect.set(_x, _y, _w, _h); // Set the position and dimensions of the button
 }
 //*/


/**
 * setPosition
 * Sets the position of the button.
 *
 * @param rectPos: A vector representing the new position of the button
 */
void Button::setPosition(ofVec2f rectPos)
{
	/// Set the position of the button
	rect.set(rectPos.x, rectPos.y, rect.width, rect.height); // Set the position of the button, keeping its dimensions the same
}

/**
 * set
 * Sets the position and size of the button.
 *
 * @param rectPos: A vector representing the new position of the button
 * @param rectSize: A vector representing the new size of the button
 */
void Button::set(ofVec2f rectPos, ofVec2f rectSize)
{
	/// Set the position and size of the button
	rect.set(rectPos.x, rectPos.y, rectSize.x, rectSize.y); // Set the position and size of the button
}

/**
 * draw
 * Draws the button on the screen.
 */
void Button::draw()
{
	ofFill(); // Fill the button
	if (isPressed) // If the button is pressed
	{
		ofSetColor(0, 0, 255, 127); // Set the color to blue
	}
	else // If the button is not pressed
	{
		ofSetColor(140, 140, 140, 127); // Set the color to gray
	}
	ofDrawRectRounded(rect, rect.width*0.25); // Draw the button as a rounded rectangle
	ofNoFill(); // Do not fill the button
	ofSetColor(191, 191, 191); // Set the color to light gray
	ofDrawRectangle(rect); // Draw the button as a rectangle
	ofSetColor(255); // Set the color to white
	ofDrawBitmapString(label, rect.x + rect.width + 10, rect.y + rect.height * 0.5 + 4); // Draw the label of the button
}

/**
 * mousePressed
 * Changes the state of the button when the mouse is pressed.
 *
 * @param x: The x-coordinate of the mouse position
 * @param y: The y-coordinate of the mouse position
 * @param button: The mouse button that was pressed
 */
void Button::mousePressed(int x, int y, int button)
{
	/// Change the state of the button when the mouse is pressed
	if (rect.inside(x, y)) // If the mouse is inside the button
	{
		isPressed = !isPressed; // Toggle the state of the button
		
		if (onClick) // Check if callback is set
		{
			onClick(); // Call the callback function
		}
	}
}

/**
 * mouseReleased
 * Changes the state of the button when the mouse is released.
 *
 * @param x: The x-coordinate of the mouse position
 * @param y: The y-coordinate of the mouse position
 * @param button: The mouse button that was released
 */
void Button::mouseReleased(int x, int y, int button)
{
	/// Change the state of the button when the mouse is released
	isPressed = false; // Set the state of the button to not pressed
}












/**
 * Toggle
 * Default constructor that initializes a Toggle object with default values.
 */
Toggle::Toggle()
{
	/// Set default values
	label = ""; // Set the toggle label to an empty string
	rect = ofRectangle(); // Initialize the toggle rectangle with default values
	isOn = false; // Set the toggle state to off
}


/**
 * Toggle
 * Parameterized constructor that initializes a Toggle object with specified label, position, dimensions, and state.
 *
 * @param _label: The label for the toggle
 * @param _x: The x-coordinate of the toggle position
 * @param _y: The y-coordinate of the toggle position
 * @param _w: The width of the toggle
 * @param _h: The height of the toggle
 * @param _isOn: The state of the toggle
 */
Toggle::Toggle(std::string _label, float _x, float _y, float _w, float _h, bool _isOn)
{
	/// Assign the parameter values to the object
	label = _label; // Set the label of the toggle
	rect.set(_x, _y, _w, _h); // Set the position and dimensions of the toggle
	isOn = _isOn; // Set the state of the toggle
}



/**
 * Toggle
 * Parameterized constructor that initializes a Toggle object with specified label, position, dimensions, and state.
 *
 * @param _label: The label for the toggle
 * @param _x: The x-coordinate of the toggle position
 * @param _y: The y-coordinate of the toggle position
 * @param _w: The width of the toggle
 * @param _h: The height of the toggle
 * @param _isOn: The state of the toggle
 */
Toggle::Toggle(std::string _label, float _x, float _y, float _w, float _h, bool _isOn, std::function<void()> callback) : onClick(callback) // Set the callback function for the button
{
	/// Assign the parameter values to the object
	label = _label; // Set the label of the toggle
	rect.set(_x, _y, _w, _h); // Set the position and dimensions of the toggle
	isOn = _isOn; // Set the state of the toggle
}


/**
 * setPosition
 * Sets the position of the toggle.
 *
 * @param rectPos: A vector representing the new position of the toggle
 */
void Toggle::setPosition(ofVec2f rectPos)
{
	/// Set the position of the toggle
	rect.set(rectPos.x, rectPos.y, rect.width, rect.height); // Set the position of the toggle, keeping its dimensions the same
}




void Toggle::callbackUpdate()
{
	if(isOn) // If the toggle is on
	{
		if(onClick) // Check if callback is set
		{
			onClick(); // Call the callback function... ensures the callback function is continuously called while the toggle is on
		}
	}
}




/**
 * draw
 * Draws the toggle on the screen.
 */
void Toggle::draw()
{
	ofFill(); // Fill the toggle
	ofSetColor(170, 170, 170, 191.25); // Set the color to a light gray
	ofDrawRectRounded(rect, rect.width*0.25); // Draw the toggle as a rounded rectangle
	
	if(isOn) // If the toggle is on
	{
		ofRectangle onRect;
		onRect.set(rect.x + rect.width*0.5 + 1, rect.y, rect.width*0.5, rect.height);
		ofSetColor(0, 0, 255); // Set the color to blue
		ofDrawRectRounded(rect, rect.width*0.25);
		
		if(onClick) // Check if callback is set
		{
			onClick(); // Call the callback function... this call is included in the draw function to ensure the callback function is continuously called while the toggle is on
		}
	}
	
	ofNoFill(); // Do not fill the toggle
	ofSetColor(111, 111, 111); // Set the color to a dark gray
	ofSetLineWidth(2); // Set the line width
	ofDrawRectangle(rect.x - 1, rect.y - 1, rect.width + 2, rect.height + 2); // Draw an outline around the toggle
	ofSetColor(255, 255, 255); // Set the color to white
	ofDrawBitmapString(label, rect.x + rect.width + 10, rect.y + rect.height * 0.5 + 4); // Draw the label of the toggle
}


/**
 * mousePressed
 * Changes the state of the toggle when the mouse is pressed.
 *
 * @param x: The x-coordinate of the mouse position
 * @param y: The y-coordinate of the mouse position
 * @param button: The mouse button that was pressed
 */
void Toggle::mousePressed(int x, int y, int button)
{
	/// Change the state of the toggle when the mouse is pressed
	if (rect.inside(x, y)) // If the mouse is inside the toggle
	{
		isOn = !isOn; // Toggle the state of the toggle
		
		if(onClick && isOn) // Check if callback is set
		{
			onClick(); // Call the callback function
		}
	}
}












/**
 * TextField
 *
 * Default constructor
 * Initializes a TextField object with default values
 */
TextField::TextField()
{
	/// The constructor initializes the TextField object with default values
	inputInRange = true;
}


/**
 * TextField
 * Parameterized constructor
 *
 * @param _label: label of the TextField object
 * @param _x: x-coordinate of the TextField object
 * @param _y: y-coordinate of the TextField object
 * @param _w: width of the TextField object
 * @param _h: height of the TextField object
 * @param _min: minimum valid value for the TextField object
 * @param _max: maximum valid value for the TextField object
 * @param &_value: reference to the value of the TextField object
 * @param _precision: precision of the value displayed in the TextField object
 */
TextField::TextField(std::string _label, float _x, float _y, float _w, float _h, float _min, float _max, double &_value, int _precision) : label(_label), rect(_x, _y, _w, _h), min(_min), max(_max), precision(_precision)
{
	/// The constructor initializes the TextField object with provided values and sets up additional interface elements
	resetButton = Button("Reset " + label, _x + _w + 35, _y, 15, 15);
	meanButton = Button("Set Mean " + label, _x + _w + 35, _y + _h*1.25, 15, 15);
	
	value = &_value;
	
	isTyping = false;
	inputInRange = true;
	warningMode = false;
	inputString = ofToString(_value, _precision);
	currentString = ofToString(_value, _precision);
}


/**
 * setPosition
 * Sets the position of the TextField object
 *
 * @param rectPos: a vector representing the new position of the TextField object
 */
void TextField::setPosition(ofVec2f rectPos)
{
	/// The function sets the position of the TextField object and its associated interface elements
	rect.set(rectPos.x, rectPos.y, rect.width, rect.height);
	resetButton.set(ofVec2f(rectPos.x + rect.width + 35, rectPos.y - rect.height * 0.28125), ofVec2f(15, 15));
	meanButton.set(ofVec2f(rectPos.x + rect.width + 35, rectPos.y + rect.height * 0.5625), ofVec2f(15, 15));
}


/**
 * draw
 *
 * This function is responsible for drawing the TextField object on the screen.
 * It handles the visual representation of the TextField object, including the text,
 * the rectangle that represents the TextField object, and the associated buttons.
 * It also manages the visual feedback for user interaction, such as changing the line
 *  width and color when the user is typing, and displaying a warning message when the
 *  input is out of range or the value is greater than the minimum allowed value.
 */
void TextField::draw()
{
	/// Set the initial visual parameters
	ofSetColor(255); // Set the color to white
	ofSetLineWidth(1); // Set the line width to 1
	
	/// Check if the user is currently typing in the TextField object, if so, change the line width and color to indicate this.
	if(isTyping)
	{
		ofSetLineWidth(3); // Increase the line width to indicate typing
		ofSetColor(44,44,255); // Change the color to blue
	}
	else
	{
		ofSetColor(127); // Set the color to gray if not typing
	}
	
	
	
	/// Draw the rectangle that represents the TextField object
	ofDrawRectangle(rect);
	
	
	
	/// Reset the line width for drawing the text and buttons
	ofSetLineWidth(1);
	
	
	
	/// Draw the text inside the TextField object
	ofSetColor(255); // Set the color to white
	if(isTyping)
	{
		// Display the current string if the user is typing
		ofDrawBitmapString(label + ": " + currentString, rect.x + 5, rect.y + rect.height * 0.6125);
	}
	else
	{
		// Display the value with a precision of 15 if the user is not typing
		ofDrawBitmapString(label + ": " + ofToString(value, 15), rect.x + 5, rect.y + rect.height * 0.6125);
	}
	
	
	
	/// Draw the reset and mean buttons
	resetButton.draw();
	meanButton.draw();
	
	
	
	/// Display a warning message if the input is out of range or if the value is greater than the minimum allowed value.
	if(!inputInRange || *value > min)
	{
		warningMode = true; // Enable warning mode
		
		ofSetColor(255,0,0); // Set the color to red for the warning message
		ofDrawBitmapString("WARNING: ", rect.x-5, rect.y + rect.height + 25);
		ofSetColor(255); // Reset the color to white
		if(!inputInRange)
		{
			// Display a warning message about the input range
			ofDrawBitmapString("         Please enter a value in the range: \n[" + ofToString(min) + ", " + ofToString(max) + "]", rect.x-5, rect.y + rect.height + 25);
		}
		else
		{
			// Display a warning message about the violation of energy conservation
			ofDrawBitmapString("         Modifying preconfigured simulation paramaters \nmay result in inaccuracies or unexpected behaviors.", rect.x-5, rect.y + rect.height + 25);
			
		}
	}
	else if (inputInRange && *value == min)
	{
		warningMode = false; // Disable warning mode if the input is in range and the value is equal to the minimum
	}
}


/**
 * mousePressed
 *
 * This function is called when the mouse button is pressed. It checks if the mouse cursor is inside the TextField object or its buttons, and performs actions accordingly.
 *
 * @param x: The x-coordinate of the mouse cursor
 * @param y: The y-coordinate of the mouse cursor
 * @param button: The mouse button that was pressed
 */
void TextField::mousePressed(int x, int y, int button)
{
	// Pass the mouse pressed event to the buttons.
	resetButton.mousePressed(x, y, button);
	meanButton.mousePressed(x, y, button);
	
	// If the mouse cursor is inside the TextField object, set the isTyping flag to true and clear the input string.
	if(rect.inside(x,y))
	{
		isTyping = true;
		inputString.clear();
		inputString += currentString;
	}
	// If the mouse cursor is not inside the TextField object, set the isTyping flag to false.
	else
	{
		isTyping = false;
	}
	
	
	
	// Check if the reset or mean buttons were pressed, and updates the value and input string accordingly.
	if (resetButton.isPressed)
	{
		// Reset the value to the minimum value.
		*value = min;
		// Update the input string.
		inputString = ofToString(value, 15);
		currentString = inputString;
	}
	if (meanButton.isPressed)
	{
		/// Calculate a reasonable average and then set the value to the reasonable average(uses several statistical methods to compute a reasonable mean value, see the methods in "StatisticalMethods.hpp" header file)
		//double reasonableAverage = ComputeReasonableAverage(min, max);
		double reasonableAverage = ComputeReasonableMean(min, max, *value);
		*value = reasonableAverage;
		
		
		/// Update the input string.
		inputString = ofToString(*value, 15);
		currentString = inputString;
	}
}


/**
 * mouseReleased
 *
 * This function handles the mouse released event for the TextField class.
 * It is responsible for passing the mouse released event to the resetButton and meanButton objects.
 * This is crucial for the functionality of the TextField class as it allows the TextField to respond to user interactions.
 * The resetButton and meanButton objects are instances of the Button class, which have their own mouseReleased methods.
 * These methods handle the logic for when the mouse button is released over the respective Button objects.
 *
 * @param x: The x-coordinate of the mouse cursor
 * @param y: The y-coordinate of the mouse cursor
 * @param button: The mouse button that was released
 */
void TextField::mouseReleased(int x, int y, int button)
{
	// Pass the mouse released event to the resetButton object.
	resetButton.mouseReleased(x, y, button);
	
	// Pass the mouse released event to the meanButton object.
	meanButton.mouseReleased(x, y, button);
}

/**
 * keyReleased
 *
 * This function handles the key released event for the TextField class.
 * It is responsible for capturing and processing the user's input.
 * The function checks the ASCII value of the key to determine if it is a printable character.
 * If the key is a printable character, it is added to the inputString and currentString.
 * If the key is the backspace key and the inputString is not empty, the last character is removed from the inputString.
 * If the key is the enter key, it calls the validateAndSetValue function to validate the input and update the value of the TextField.
 *
 * @param key: The key that was released
 */
void TextField::keyReleased(int key)
{
	/// Only append if the key is a printable character
	if (key >= 32 && key <= 126)
	{
		// Add the character to the inputString
		inputString += static_cast<char>(key);
		// Add the character to the currentString
		currentString += static_cast<char>(key);
	}
	/// Account for keys that are not printable characters, but still can be accepeted as entries
	else if (key == OF_KEY_BACKSPACE) // Allow the user to use the backspace key to delete previous entries
	{
		// Check if the previously submitted inputString(records accepted textfield submissions) is not empty
		if(!inputString.empty())
		{
			// Remove the last character from the inputString
			inputString.pop_back();
		}
		
		
		// Check if the currentString(tracks textfield string as user is typing it) is not empty
		if(!currentString.empty())
		{
			// Remove the last character from the currentString
			currentString.pop_back();
		}
	}
	
	/// The enter key is one of the ways that user-typed entries can be submitted(the other has to do with the mouse)
	if (key == OF_KEY_RETURN)
	{
		// Ensure the input is valid and attempt to update the value by it
		validateAndSetValue();
	}
}


/**
 * validateAndSetValue
 *
 * This function validates the user's input and updates the value of the TextField.
 * It first converts the inputString to a double using a stringstream.
 * It then checks if the value is within the allowed range (min to max).
 * If the value is within the range, it updates the value of the TextField, sets the inputInRange flag to true, the isTyping flag to false, and the warningMode flag to false.
 * If the value is not within the range, it sets the inputInRange flag to false and the warningMode flag to true.
 */
void TextField::validateAndSetValue()
{
	/// Validate the input and update the value.
	std::stringstream ss(inputString); // Create a stringstream from the inputString
	double tempValue; // Declare a temporary variable to store the value
	ss >> tempValue; // Convert the inputString to a double
	
	
	if (tempValue >= min && tempValue <= max) // Ensure the value is within the allowed range
	{
		*value = tempValue; // Update the value
		inputInRange = true; // Set the inputInRange flag to true
		isTyping = false; // Set the isTyping flag to false
		warningMode = false; // Set the warningMode flag to false
	}
	else // Handle the case when the value is not within the allowed range
	{
		inputInRange = false; // Set the inputInRange flag to false
		warningMode = true; // Set the warningMode flag to true
	}
}








/**
 * Tab
 *
 * Default constructor for the Tab class.
 * Initializes a Tab object with default values.
 */
Tab::Tab()
{
	/// Initialize member variables with default values.
	label = "";
	rect = ofRectangle();
	isPressed = false;
}


/**
 * Tab
 *
 * Parameterized constructor for the Tab class.
 * Initializes a Tab object with the provided values.
 *
 * @param _label: Label of the Tab object
 * @param _x: x-coordinate of the Tab object
 * @param _y: y-coordinate of the Tab object
 * @param _w: Width of the Tab object
 * @param _h: Height of the Tab object
 * @param _isPressed: State of the Tab object
 */
Tab::Tab(std::string _label, float _x, float _y, float _w, float _h, bool _isPressed)
{
	/// Initialize member variables with provided values.
	isPressed = _isPressed;
	label = _label;
	rect.set(_x, _y, _w, _h);
}


/**
 * Tab
 *
 * Parameterized constructor for the Tab class.
 * Initializes a Tab object with the provided values.
 *
 * @param _label: Label of the Tab object
 * @param _x: x-coordinate of the Tab object
 * @param _y: y-coordinate of the Tab object
 * @param _w: Width of the Tab object
 * @param _h: Height of the Tab object
 * @param _isPressed: State of the Tab object
 */
Tab::Tab(std::string _label, float _x, float _y, float _w, float _h, bool _isPressed,  std::function<void()> callback) : onClick(callback)  // Set the callback function for the button
{
	/// Initialize member variables with provided values.
	isPressed = _isPressed;
	label = _label;
	rect.set(_x, _y, _w, _h);
}


/**
 * setPosition
 * Sets the position of the Tab object.
 *
 * @param rectPos: A vector representing the new position of the Tab object
 */
void Tab::setPosition(ofVec2f rectPos)
{
	/// Set the position of the Tab object.
	rect.set(rectPos.x, rectPos.y, rect.width, rect.height);
}

/**
 * set
 * Sets the position and size of the Tab object.
 *
 * @param rectPos: A vector representing the new position of the Tab object
 * @param rectSize: A vector representing the new size of the Tab object
 */
void Tab::set(ofVec2f rectPos, ofVec2f rectSize)
{
	/// Set the position and size of the Tab object.
	rect.set(rectPos.x, rectPos.y, rectSize.x, rectSize.y);
}


/**
 * draw
 *
 * The draw function is responsible for rendering the Tab object on the screen.
 * It first sets up the drawing properties such as fill, color, and line width.
 * Then, it draws the rectangle representing the Tab object. Depending on the state of the
 * Tab object (whether it is pressed or not), it draws a line in the middle of the rectangle.
 * If the Tab object is not pressed, an additional line is drawn perpendicular to the first one,
 * dividing the rectangle into four equal parts.
 */
void Tab::draw()
{
	/// Set the initial visual parameters
	ofNoFill();
	ofSetColor(255, 255, 255, 77); // Set the color to white with a transparency of 77
	ofSetLineWidth(2); // Set the line width for the rectangle to 2
	
	
	
	/// Draw the rectangle representing the Tab object.
	ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
	
	
	// Reset the line width to 1 for the lines inside the rectangle.
	ofSetLineWidth(1);
	
	
	/// Draw a line in the middle of the rectangle, if the Tab object is pressed, only one line is drawn.
	if (isPressed)
	{
		ofDrawLine(rect.x + 2, rect.y + rect.height * 0.5, rect.x + rect.width - 2, rect.y + rect.height * 0.5);
	}
	else   // If the Tab object is not pressed, an additional line is drawn perpendicular to the first one.
	{
		ofDrawLine(rect.x + 2, rect.y + rect.height * 0.5, rect.x + rect.width - 2, rect.y + rect.height * 0.5);
		ofDrawLine(rect.x + rect.width * 0.5, rect.y + 2, rect.x + rect.width * 0.5, rect.y + rect.height - 2);
	}
}


/**
 * mousePressed
 * Handles the mouse pressed event for the Tab object.
 *
 * @param x: The x-coordinate of the mouse cursor
 * @param y: The y-coordinate of the mouse cursor
 * @param button: The mouse button that was pressed
 */
void Tab::mousePressed(int x, int y, int button)
{
	/// Handle the mouse pressed event.
	if (rect.inside(x, y))
	{
		isPressed = !isPressed;
		
		if (onClick) // Check if callback is set
		{
			onClick(); // Call the callback function
		}
	}
}















