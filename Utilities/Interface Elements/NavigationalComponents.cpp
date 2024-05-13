//  NavigationalComponents.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#include "NavigationalComponents.hpp"





/**
 * Slider
 *
 * Default constructor for the Slider class.
 * Initializes the slider with no label, default position, size, and range.
 */
Slider::Slider()
{
	/// Set default values
	label = ""; // Set the label as an empty string
	rect = ofRectangle(); //  Initialize the rectangle representing the slider's position and size
	min = 0;
	max = 0;
	value = 0;
}


/**
 * Slider
 *
 * Constructor for the Slider class. Initializes the slider with a label, specific position, size, and range.
 *
 * @param _label: The label for the slider
 * @param _x: The x-coordinate of the slider's position
 * @param _y: The y-coordinate of the slider's position
 * @param _w: The width of the slider
 * @param _h: The height of the slider
 * @param _min: The minimum value of the slider
 * @param _max: The maximum value of the slider
 * @param _value: The initial value of the slider
 * @return None
 */
Slider::Slider(std::string _label, float _x, float _y, float _w, float _h, float _min, float _max, float &_value)
{
	/// Assign the label, minimum value, maximum value, and current value of the slider
	label = _label;
	min = _min;
	max = _max;
	value = &_value;
	
	/// Set the position and size of the slider
	rect.set(_x, _y, _w, _h);
}


/**
 * Slider
 *
 * Constructor for the Slider class. Initializes the slider with a label, specific position,
 * size, range, and precision of the value displayed in the Slider object.
 *
 * @param _label: The label for the slider
 * @param _x: The x-coordinate of the slider's position
 * @param _y: The y-coordinate of the slider's position
 * @param _w: The width of the slider
 * @param _h: The height of the slider
 * @param _min: The minimum value of the slider
 * @param _max: The maximum value of the slider
 * @param _value: The initial value of the slider
 * @param _precision: precision needed to fully capture the value displayed in the Slider object
 */
Slider::Slider(std::string _label, float _x, float _y, float _w, float _h, float _min, float _max, float &_value, int _precision)
{
	label = _label;
	rect.set(_x, _y, _w, _h);
	min = _min;
	max = _max;
	value = &_value;
	precision = _precision;
}


/**
 * setPosition
 * Sets the position of the slider while keeping the same width and height.
 *
 * @param rectPos: The new position of the slider
 */
void Slider::setPosition(ofVec2f rectPos)
{
	// Set the new position of the slider
	rect.set(rectPos.x, rectPos.y, rect.width, rect.height);
}


/**
 * draw
 *
 * Draws the slider on the screen. The slider is represented by a rectangle.
 * The current value of the slider is represented by a smaller filled rectangle inside the slider rectangle.
 */
void Slider::draw()
{
	/// Set the color and draw the outline of the slider rectangle
	ofNoFill();
	ofSetColor(127);
	ofDrawRectangle(rect);
	
	/// Calculate the x-coordinate of the filled rectangle inside the slider rectangle
	float x = ofMap(*value, min, max, rect.x, rect.x + rect.width);
	
	/// Set the color and draw the filled rectangle
	ofSetColor(191);
	ofFill();
	ofDrawRectangle(x - 5, rect.y, 10, rect.height);
	
	/// Set the color and draw the label and the current value of the slider
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(label + ": " + ofToString(value, 3), rect.x + rect.width + 10, rect.y + rect.height * 0.5);
}


/**
 * mousePressed
 *
 * Handles the mouse pressed event. If the mouse is pressed inside the slider rectangle,
 * sets isDragging to true. Otherwise, sets isDragging to false.
 *
 * @param x: The x-coordinate of the mouse press
 * @param y: The y-coordinate of the mouse press
 * @param button: The mouse button that was pressed
 */
void Slider::mousePressed(int x, int y, int button)
{
	/// Check if the mouse press was inside the slider rectangle
	if (rect.inside(x, y))
	{
		/// If the mouse press was inside the slider rectangle, set isDragging to true
		isDragging = true;
	}
	else
	{
		/// If the mouse press was not inside the slider rectangle, set isDragging to false
		isDragging = false;
	}
}


/**
 * mouseDragged
 *
 * Handles the mouse dragged event. If the mouse is being dragged and isDragging is true, updates the value of the slider to correspond to the x-coordinate of the mouse.
 *
 * @param x: The x-coordinate of the mouse drag
 * @param y: The y-coordinate of the mouse drag
 * @param button: The mouse button that is being dragged
 */
void Slider::mouseDragged(int x, int y, int button)
{
	/// Check if the mouse is being dragged and isDragging is true
	if (isDragging)
	{
		/// If the mouse is being dragged and isDragging is true, calculate the new value of the slider
		float newValue = ofMap(x, rect.x, rect.x + rect.width, min, max, true);
		
		/// Update the value of the slider
		*value = newValue;
		
	}
}


/**
 * mouseReleased
 * Handles the mouse released event. Whenever the mouse is released, sets isDragging to false.
 *
 * @param x: The x-coordinate of the mouse release
 * @param y: The y-coordinate of the mouse release
 * @param button: The mouse button that was released
 */
void Slider::mouseReleased(int x, int y, int button)
{
	/// Whenever the mouse is released, set isDragging to false
	isDragging = false;
}

















/**
 * ~Table
 * Destructor for the Table class. Clears all the elements in the table.
 */
Table::~Table()
{
	/// Call the clear function to clear all the elements in the table
	clear();
}


/**
 * Table
 *
 * Constructor for the Table class. Initializes the table with a label, specific position, size, and opened state.
 *
 * @param _label: The label for the table
 * @param _x: The x-coordinate of the table's position
 * @param _y: The y-coordinate of the table's position
 * @param _w: The width of the table
 * @param _h: The height of the table
 * @param _isOpened: The opened state of the table
 */
Table::Table(std::string _label, float _x, float _y, float _w, float _h, bool _isOpened)
{
	/// Assign the label, opened state, and type of the table
	label = _label;
	isOpened = _isOpened;
	tableType = 0;  // Initialize the table type
	
	
	/// Initialize the rectangle
	labelRect = GetBoundingBox(label, _x, _y + _h*0.3125, 1, 1); // Set the rectangle representing the label's bounding box
	tableTab.set(ofVec2f(labelRect.x + labelRect.width + 10, _y - _h * 0.5 + 2), ofVec2f(_w, _h)); // Set the rectangle representing the table's position and size
	
	
	
	//scaleTable = 1;
	//tableOffset = 0;
}


/**
 * Table
 *
 * Constructor for the Table class. Initializes the table with a label, specific position, size, opened state, and type.
 *
 * @param _label: The label for the table
 * @param _x: The x-coordinate of the table's position
 * @param _y: The y-coordinate of the table's position
 * @param _w: The width of the table
 * @param _h: The height of the table
 * @param _isOpened: The opened state of the table
 * @param _tableType: The type of the table
 */
Table::Table(std::string _label, float _x, float _y, float _w, float _h, bool _isOpened, int _tableType)
{
	/// Assign the label, opened state, and type of the table
	label = _label;
	isOpened = _isOpened;
	tableType = _tableType;
	
	
	
	/// Initialize the rectangle
	labelRect = GetBoundingBox(label, _x, _y + _h*0.3125, 1, 1); // Set the rectangle representing the label's bounding box
	tableTab.set(ofVec2f(labelRect.x + labelRect.width + 10, _y - _h * 0.5 + 2), ofVec2f(_w, _h)); // Set the rectangle representing the table's position and size
	
	
	
	//scaleTable = 1;
	//tableOffset = 0;
}


//
/*
 Table::Table(std::string _label, float _x, float _y, float _w, float _h, bool _isOpened, int _scaleTable, int _tableOffset)
 {
 label = _label;
 isOpened = _isOpened;
 labelRect = GetBoundingBox(label, _x, _y + _h*0.3125, 1, 1);
 tableTab.set(ofVec2f(labelRect.x + labelRect.width + 10, _y - _h * 0.5 + 2), ofVec2f(_w, _h));
 scaleTable = _scaleTable;
 tableOffset = _tableOffset;
 tableType = 0;
 }
 //*/

/**
 * addSliderElement
 * Adds a slider element to the table.
 *
 * @param _sliderElement: A pointer to the slider element to be added
 */
void Table::addSliderElement(Slider* &_sliderElement)
{
	/// Add the slider element to the list of slider elements
	sliderElements.emplace_back(_sliderElement);
}


/**
 * addButtonElement
 * Adds a button element to the table.
 *
 * @param _buttonElement: A pointer to the button element to be added
 */
void Table::addButtonElement(Button* &_buttonElement)
{
	/// Add the button element to the list of button elements
	buttonElements.emplace_back(_buttonElement);
}


/**
 * addToggleElement
 * Adds a toggle element to the table.
 *
 * @param _toggleElement: A pointer to the toggle element to be added
 */
void Table::addToggleElement(Toggle* &_toggleElement)
{
	/// Add the toggle element to the list of toggle elements
	toggleElements.emplace_back(_toggleElement);
}


/**
 * addTextFieldElement
 * Adds a text field element to the table.
 *
 * @param _textFieldElement: A pointer to the text field element to be added
 */
void Table::addTextFieldElement(TextField* &_textFieldElement)
{
	/// Add the text field element to the list of text field elements
	textfieldElements.emplace_back(_textFieldElement);
}
/**
 * tableDimensions
 *
 * This function calculates and returns the dimensions of the table based on its current state and the elements it contains.
 * It iterates through each type of elements in the table (Slider, Button, Toggle, TextField). For each element,
 * it calculates the bounding box for the label and adjusts the width and height of the table accordingly.
 *
 * If the table is open, the function will iterate through each type of element in the
 * table(slider, button, toggle, textfield) and if the element's type is not empty,
 * it calculates dimensions to enclose at least the widest table contained within,
 * and if the tableHeight is less than a certain value, it adjusts the tableHeight.
 * If the table is closed, it calculates the bounding box for the label and adjusts the width and height of the table accordingly.
 * Lastly, if the tableType is 1, the function adjusts the width to be double and the height to be half.
 *
 * @return ofVec2f: The width and height of the table
 */
ofVec2f Table::tableDimensions()
{
	/// Initialize tableHeight and tableWidth
	float tableHeight, tableWidth;
	
	/// If the table is open
	if(isOpened)
	{
		/// Check if there are any slider elements
		if (!sliderElements.empty())
		{
			/// Iterate through each slider element
			for (auto& slider : sliderElements)
			{
				ofRectangle labilRect = GetBoundingBox(slider->label, slider->rect.x, slider->rect.y, 1, 1); // Calculate the bounding box for the label
				
				
				/// Adjust the width of the table to enclose at least the widest table contained within
				if(labilRect.width > tableWidth || slider->rect.width > tableWidth)
				{
					tableWidth = std::max(labilRect.width, slider->rect.width);
				}
				
				tableHeight += labelRect.height; // Adjust the height of the table
			}
		}
		
		/// Repeat the process for button elements
		if (!buttonElements.empty())
		{
			for (auto& myButton : buttonElements)
			{
				ofRectangle labilRect = GetBoundingBox(myButton->label, myButton->rect.x, myButton->rect.y, 1, 1);
				if(labilRect.width > tableWidth || myButton->rect.width > tableWidth)
				{
					tableWidth = std::max(labilRect.width, myButton->rect.width);
				}
				tableHeight += labelRect.height;
			}
		}
		
		/// Repeat the process for toggle elements
		if (!toggleElements.empty())
		{
			for (auto& toggle : toggleElements)
			{
				ofRectangle labilRect = GetBoundingBox(toggle->label, toggle->rect.x, toggle->rect.y, 1, 1);
				if(labilRect.width > tableWidth || toggle->rect.width > tableWidth)
				{
					tableWidth = std::max(labilRect.width, toggle->rect.width);
				}
				tableHeight += labelRect.height;
			}
		}
		
		/// Repeat the process for textfield elements
		if (!textfieldElements.empty())
		{
			for (auto& textField : textfieldElements)
			{
				ofRectangle labilRect = GetBoundingBox(textField->label, textField->rect.x, textField->rect.y, 1, 1);
				if(labilRect.width > tableWidth || textField->rect.width > tableWidth)
				{
					tableWidth = std::max(labilRect.width, textField->rect.width);
				}
				tableHeight += labelRect.height;
			}
		}
		
		
		
		/// The acceptable table height is at least twice the height of the tab rectangle multiplied by the total number of elements
		/// If the tableHeight is less than the acceptable height, the tableHeight is set to be the determined acceptable height
		if(tableHeight < (tableTab.rect.height * 2 * (sliderElements.size() + buttonElements.size() + toggleElements.size())))
		{
			tableHeight = (tableTab.rect.height * 2 * (sliderElements.size() + buttonElements.size() + toggleElements.size()));
		}
	}
	
	/// Else the table is closed, and now the function calculates the bounding box for the label and adjusts the width and height of the table accordingly
	else
	{
		ofRectangle labilRect = GetBoundingBox(label, labelRect.x, labelRect.y, 1, 1); // Calculate bounding box for the label
		
		/// Adjust width and height of the table accordingly
		tableHeight = labilRect.height;
		if(labilRect.width > tableWidth || labelRect.width > tableWidth)
		{
			tableWidth = std::max(labilRect.width, labelRect.width);
		}
	}
	
	
	/// Adjusts the width and height of the table based on the table type
	if(tableType == 1)
	{
		tableWidth *= 2;
		tableHeight *= 0.5;
	}
	return ofVec2f(tableWidth, tableHeight);
}


/**
 * setPosition
 * Sets the position of the table. Adjusts the position of the label and tableTab according to the new position.
 *
 * @param rectPos: The new position of the table
 */
void Table::setPosition(ofVec2f rectPos)
{
	/// Calculates the bounding box for the label based on the new position
	labelRect = GetBoundingBox(label, rectPos.x, rectPos.y + tableTab.rect.height * 0.375, 1, 1);
	
	/// Sets the position of the tableTab based on the new position and the dimensions of the labelRect
	tableTab.setPosition(ofVec2f(labelRect.x + labelRect.width + 10, rectPos.y - tableTab.rect.height * 0.5 + 2));
}



void Table::callbackUpdate()
{
	if(!toggleElements.empty())
	{
		for(auto& toggle : toggleElements)
		{
			toggle->callbackUpdate();
		}
	}
}


/**
 * draw
 * This function is responsible for drawing the table and its elements. It first sets the color and draws the label.
 * Then it draws the tableTab. If the table is opened, it calculates the dimensions of the table and determines the size
 * and position of the opened table rectangle based on the position of the tableTab. It then draws the opened table rectangle.
 * After that, it calculates the y position and height of the table elements and draws and positions the slider elements,
 * textField elements, button elements, and toggle elements accordingly.
 */
void Table::draw()
{
	// Get the window dimensions
	float xWind = ofGetWidth(), yWind = ofGetHeight();
	
	// Set color to white
	ofSetColor(255, 255, 255);
	
	// Draw the label
	ofDrawBitmapString(label, labelRect.x, labelRect.y);
	
	// Set color to white with 50% transparency
	ofSetColor(255, 255, 255, 127);
	
	// Draw the tableTab
	tableTab.draw();
	
	
	// If the table is opened
	if (isOpened)
	{
		//
		/*
		 if (!textfieldElements.empty())
		 {
		 for (auto& textField : textfieldElements)
		 {
		 if(textField->warningMode)
		 {
		 tableOffset = textField->rect.height;
		 }
		 else
		 {
		 tableOffset = 0;
		 }
		 }
		 }
		 //*/
		
		
		
		/// Calculate the dimensions of the table
		ofVec2f tableBounds = tableDimensions();
		//float scaleHeight = scaleTable + (1*scaleTable);
		//scaleHeight = (scaleHeight/(scaleTable+1));
		float totalHeight = tableBounds.y; //(tableTab.rect.height * 2 * (sliderElements.size() + buttonElements.size() + toggleElements.size()));  // Determine the size and position of the opened table rectangle
		float openedTableWidth = tableBounds.x;//tableTab.rect.width * 12;
		float openedTableHeight;
		
		
		
		
		/// Determine the size and position of the opened table rectangle
		openedTableHeight = totalHeight;
		
		float openedTableX, openedTableY;
		// Determine the position of the opened table rectangle based on the position of the tableTab
		// The four conditions correspond to the four quadrants of the window
		if (tableTab.rect.x < xWind * 0.5 && tableTab.rect.y < yWind * 0.5) //top left
		{
			openedTableX = tableTab.rect.x + tableTab.rect.width + 15;
			openedTableY = tableTab.rect.y + tableTab.rect.height * 0.5;
		}
		else if (tableTab.rect.x >= xWind * 0.5 && tableTab.rect.y < yWind * 0.5) //top right
		{
			openedTableX = tableTab.rect.x - openedTableWidth - tableTab.rect.width;
			openedTableY = tableTab.rect.y + tableTab.rect.height*2;
		}
		else if (tableTab.rect.x < xWind * 0.5 && tableTab.rect.y >= yWind * 0.5) //bottom left
		{
			openedTableX = tableTab.rect.x + tableTab.rect.width + 15;
			openedTableY = tableTab.rect.y - openedTableHeight - tableTab.rect.height * 2;
		}
		else if (tableTab.rect.x >= xWind * 0.5 && tableTab.rect.y >= yWind * 0.5) //bottom right
		{
			openedTableX = tableTab.rect.x - openedTableWidth - tableTab.rect.width;
			openedTableY = tableTab.rect.y - openedTableHeight - tableTab.rect.height;
			openedTableWidth = openedTableWidth * 1.75;
		}
		
		
		/// Draw the opened table rectangle
		ofFill();
		ofSetColor(255, 255, 255, 18.75);
		ofDrawRectangle(openedTableX, openedTableY - tableTab.rect.height, openedTableWidth * 1.25 , openedTableHeight * 1.05);
		ofNoFill();
		
		
		
		/// Calculate the y position and height of the table elements
		float elementHeight = openedTableHeight / (sliderElements.size() + buttonElements.size() + toggleElements.size());
		float yPos = openedTableY;
		
		
		
		/// Draw and position the slider elements
		for (auto& slider : sliderElements)
		{
			slider->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
			slider->draw();
			yPos += elementHeight;
		}
		yPos += 5;
		
		
		/// Draw and position the textField elements
		for (auto& textField : textfieldElements)
		{
			textField->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos));
			textField->draw();
			yPos += elementHeight+35;
		}
		
		
		/// Draw and position the button elements
		for (auto& button : buttonElements)
		{
			button->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos ));
			button->draw();
			yPos += elementHeight;
		}
		
		
		/// Draw and position the toggle elements
		int i = 0;
		for (auto& toggle : toggleElements)
		{
			i++;
			if(!textfieldElements.empty())
			{
				if(i>3)
				{
					toggle->setPosition(ofVec2f((openedTableX + tableTab.rect.width)*1.625, (yPos - elementHeight*3) ));
				}
				else
				{
					toggle->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos ));
				}
			}
			else
			{
				toggle->setPosition(ofVec2f(openedTableX + tableTab.rect.width, yPos ));
			}
			toggle->draw();
			yPos += elementHeight;
		}
		
	}
}


void Table::exit()
{
	clear();
	
	
	if (!sliderElements.empty())
	{
		for(int i=0; i < sliderElements.size();i++)
		{
			if(sliderElements[i] != nullptr)
			{
				sliderElements.erase(sliderElements.begin()+i);
				
				delete sliderElements[i];
			}
		}
		sliderElements.clear();
	}
	
	if (!buttonElements.empty())
	{
		for(int i=0; i < buttonElements.size();i++)
		{
			if(buttonElements[i] != nullptr)
			{
				buttonElements.erase(buttonElements.begin()+i);
				
				delete buttonElements[i];
			}
		}
		buttonElements.clear();
	}
	
	
	if (!toggleElements.empty())
	{
		for(int i=0; i < toggleElements.size();i++)
		{
			if(toggleElements[i] != nullptr)
			{
				toggleElements.erase(toggleElements.begin()+i);
				
				delete toggleElements[i];
			}
		}
		toggleElements.clear();
	}
	
	if (!textfieldElements.empty())
	{
		for(int i=0; i < textfieldElements.size();i++)
		{
			if(textfieldElements[i] != nullptr)
			{
				textfieldElements.erase(textfieldElements.begin()+i);
				
				delete textfieldElements[i];
			}
		}
		textfieldElements.clear();
	}
	
}




void Table::clear()
{
	if (!sliderElements.empty())
	{
		for(int i=0; i < sliderElements.size();i++)
		{
			if(sliderElements[i] != nullptr)
			{
				sliderElements.erase(sliderElements.begin()+i);
			}
		}
		sliderElements.clear();
	}
	
	if (!buttonElements.empty())
	{
		for(int i=0; i < buttonElements.size();i++)
		{
			if(buttonElements[i] != nullptr)
			{
				buttonElements.erase(buttonElements.begin()+i);
			}
		}
		buttonElements.clear();
	}
	
	
	if (!toggleElements.empty())
	{
		for(int i=0; i < toggleElements.size();i++)
		{
			if(toggleElements[i] != nullptr)
			{
				toggleElements.erase(toggleElements.begin()+i);
			}
		}
		toggleElements.clear();
	}
	
	if (!textfieldElements.empty())
	{
		for(int i=0; i < textfieldElements.size();i++)
		{
			if(textfieldElements[i] != nullptr)
			{
				textfieldElements.erase(textfieldElements.begin()+i);
			}
		}
		textfieldElements.clear();
	}
}

void Table::keyReleased(int key)
{
	if (!textfieldElements.empty())
	{
		for (auto& textField : textfieldElements)
		{
			textField->keyReleased(key);
		}
	}
}

void Table::mousePressed(int x, int y, int button)
{
	tableTab.mousePressed(x, y, button);
	
	if (tableTab.rect.inside(x, y))
	{
		isOpened = !isOpened;
	}
	
	
	
	if (isOpened)
	{
		if (!sliderElements.empty())
		{
			for (auto& slider : sliderElements)
			{
				slider->mousePressed(x, y, button);
			}
		}
		
		if (!buttonElements.empty())
		{
			for (auto& myButton : buttonElements)
			{
				myButton->mousePressed(x, y, button);
			}
		}
		
		
		if (!toggleElements.empty())
		{
			for (auto& toggle : toggleElements)
			{
				toggle->mousePressed(x, y, button);
			}
		}
		
		
		if (!textfieldElements.empty())
		{
			for (auto& textField : textfieldElements)
			{
				textField->mousePressed(x, y, button);
			}
		}
	}
}

void Table::mouseDragged(int x, int y, int button)
{
	if (!sliderElements.empty())
	{
		for (auto& slider : sliderElements)
		{
			slider->mouseDragged(x, y, button);
		}
	}
}

void Table::mouseReleased(int x, int y, int button)
{
	if (!sliderElements.empty())
	{
		for (auto& slider : sliderElements)
		{
			slider->mouseReleased(x, y, button);
		}
	}
	
	if (!buttonElements.empty())
	{
		for (auto& myButton : buttonElements)
		{
			myButton->mouseReleased(x, y, button);
		}
	}
	
	
	if (!textfieldElements.empty())
	{
		for (auto& textField : textfieldElements)
		{
			textField->mouseReleased(x, y, button);
		}
	}
}













TableManager::TableManager()
{
	simulationMode = 0;
	
	galaxyCreationMode = false;
	isOpened = false;
}



TableManager::TableManager(int _mode, std::string _label)
{
	simulationMode = _mode;
	label = _label;
	
	galaxyCreationMode = false;
	isOpened = false;
	
	if(simulationMode == 0)
	{
		
	}
	
	labelRect = GetBoundingBox(label, 0 + ofGetWidth() * 0.01, 0 + ofGetHeight() * 0.01, 1, 1);
	rect.set(labelRect.x + labelRect.width + 10, 25, 200, 200); // `10` is a space between label and rect
	
	
	
	
}

TableManager::TableManager(int _mode, std::string _label, float _x, float _y, float _w, float _h)
{
	simulationMode = _mode;
	label = _label;
	
	galaxyCreationMode = false;
	isOpened = false;
	
	if(simulationMode == 0)
	{
		
	}
	
	labelRect = GetBoundingBox(label, _x, _y + _h*0.3125, 1, 1);
	rect.set(labelRect.x + labelRect.width + 10, _y - _h * 0.5 + 2, _w, _h); // `10` is a space between label and rect
	
	
}



TableManager::~TableManager()
{
	clear();
}




void TableManager::setPosition(ofVec2f rectPos) //adjust position and size of entire table manager based on table elements, then adjust table elements to match tableManager
{
	/**
	 * reposition tables based on which table are currently open
	 *
	 * grow or shrink table manager's menu to always enclose all tables (excluding special cases(galaxy creator))
	 *
	 * set positions and size of all tables to keep them equidistant, equally scaled, and within table manager
	 *
	 *
	 *
	 * do the above steps every time a table is opened, everytime a table is closed, and everytime the window is resized
	 *
	 * when the table is closed, set the position and size of all tables back to how they originally were (be sure to account for any change in window size)
	 
	 */
	
	labelRect = GetBoundingBox(label, rectPos.x, rectPos.y + rect.height * 0.375, 1, 1);
	rect.x = labelRect.x + labelRect.width + 10;
	rect.y = rectPos.y - rect.height * 0.5 + 2;
	
	
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->draw();
		}
	}
}



void TableManager::draw()
{
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(label, labelRect.x, labelRect.y);
	
	//need all visualization table inside one table manager
	
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->callbackUpdate();
		}
	}
	
	
	
	//depending on which tables are open, the others need to move around to make room
	// Draw the opened table rectangle
	if(isOpened)
	{
		ofFill();
		ofSetColor(222, 222, 222, 37.5);
		ofDrawRectangle(rect);
		
		
		
		
		if (!tables.empty())
		{
			
			for (auto& table : tables)
			{
				if(table->tableType == 2)
				{
					
				}
				table->draw();
			}
		}
		
		
		
		
		ofNoFill();
		ofSetColor(255, 255, 255, 77);
		ofSetLineWidth(2);
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
		ofSetLineWidth(1);
		ofDrawLine(rect.x + 2, rect.y + rect.height * 0.5, rect.x + rect.width - 2, rect.y + rect.height * 0.5);
	}
	else
	{
		ofNoFill();
		ofSetColor(255, 255, 255, 77);
		ofSetLineWidth(2);
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
		ofSetLineWidth(1);
		ofDrawLine(rect.x + rect.width * 0.5, rect.y + 2, rect.x + rect.width * 0.5, rect.y + rect.height - 2);
		ofDrawLine(rect.x + 2, rect.y + rect.height * 0.5, rect.x + rect.width - 2, rect.y + rect.height * 0.5);
	}
}

void TableManager::repositionTables()
{
	int tableManagerHeight = 0, tableManagerWidth = 0;
	
	
	if (!tables.empty())
	{
		int margin = 10;  // Margin between tables
		int currentX = margin;  // Start position x
		int currentY = margin;  // Start position y
		int maxHeightInRow = 0;  // Track the maximum height in the current row
		
		float screenWidth = ofGetWidth();  // Get the screen width from openFrameworks
		
		// Iterate over all tables to set their new positions
		for (auto& table : tables)
		{
			if(table->labelRect.width > tableManagerWidth || table->tableTab.rect.width > tableManagerWidth) //adjust width of table manager to enclose at least the widest table contained within
			{
				tableManagerWidth = std::max(table->labelRect.width, table->tableTab.rect.width);
			}
			
			ofVec2f tableSize = table->tableDimensions();  // Assume this method returns the width and height of the table
			
			// Check if adding this table would exceed the screen width
			if (currentX + tableSize.x > screenWidth)
			{
				// Move to the next row
				currentX = margin;
				currentY += maxHeightInRow + margin;
				maxHeightInRow = 0;
			}
			
			// Set the table's new position
			table->setPosition(ofVec2f(currentX, currentY));
			
			// Update currentX and maxHeightInRow for the next table
			currentX += tableSize.x + margin;
			if (tableSize.y > maxHeightInRow)
			{
				maxHeightInRow = tableSize.y;
			}
			
			
			//
			if(table->isOpened)
			{
				tableManagerHeight += table->tableTab.rect.height;
			}
			else
			{
				
			}
			tableManagerHeight += table->labelRect.height;
		}
	}
	
	rect.height += tableManagerHeight;
	rect.width = tableManagerWidth;
}

void TableManager::exit()
{
	if (!tables.empty())
	{
		for(int i=0; i < tables.size();i++)
		{
			if(tables[i] != nullptr)
			{
				tables[i]->clear();
				//tables[i]->exit();
				
				tables[i] = nullptr;
			}
		}
		tables.clear();
	}
}



void TableManager::clear()
{
	if (!tables.empty())
	{
		for(int i=0; i < tables.size();i++)
		{
			if(tables[i] != nullptr)
			{
				tables.erase(tables.begin()+i);
			}
		}
		tables.clear();
	}
}

void TableManager::keyReleased(int key)
{
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->keyReleased(key);
		}
	}
}

void TableManager::mousePressed(int x, int y, int button)
{
	if (rect.inside(x, y))
	{
		isOpened = !isOpened;
	}
	
	
	
	if (isOpened)
	{
		if(!tables.empty())
		{
			for (auto& table : tables)
			{
				table->mousePressed(x, y, button);
				
				
				if(table->tableType == 2)
				{
					if(table->isOpened)
					{
						galaxyCreationMode = true;
					}
					else
					{
						galaxyCreationMode = false;
					}
				}
			}
		}
	}
}

void TableManager::mouseDragged(int x, int y, int button)
{
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->mouseDragged(x, y, button);
		}
	}
}

void TableManager::mouseReleased(int x, int y, int button)
{
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			table->mouseReleased(x, y, button);
		}
	}
}


void TableManager::addTable(Table* &table)
{
	tables.emplace_back(table);
	
	
}


void TableManager::galaxyMode()
{
	if (!tables.empty())
	{
		for (auto& table : tables)
		{
			
			if(table->tableType == 2 && table->isOpened) //this means that the galaxy special case table is opened, in which case, close all other tables except table manager
			{
				table->isOpened = true;
				galaxyCreationMode = true;
			}
			else
			{
				galaxyCreationMode = false;
			}
		}
	}
	
	
	if(galaxyCreationMode)
	{
		for (auto& table : tables)
		{
			if(!(table->tableType == 2)) //this means that the galaxy special case table is opened, in which case, close all other tables except table manager
			{
				table->isOpened = false;
			}
			
		}
	}
}









// Constructor that initializes a RectangularGridDragSelection with a label, specific position, and size
RectangularGridDragSelection::RectangularGridDragSelection(std::string label, float _x, float _y, float _w, float _h)
: gridLabel(label), gridBounds(_x, _y, _w, _h), isPressed(false), isDragging(false), granularity(_w * 0.1) {}



// Constructor that initializes a RectangularGridDragSelection with a label, specific position, size, and min/max values for the slider
RectangularGridDragSelection::RectangularGridDragSelection(std::string label, float _x, float _y, float _w, float _h, float _min, float _max)
: gridLabel(label), gridBounds(_x, _y, _w, _h), min(_min), max(_max), isPressed(false), isDragging(false) {}




/**
 * setPosition
 * Sets the position of the top left corner of RectangularGridDragSelection while keeping the same width and height.
 *
 * @param rectPos: The new position of the slider
 */
void RectangularGridDragSelection::setPosition(ofVec2f rectPos)
{
	// Set the new position of the slider
	gridBounds.set(rectPos.x, rectPos.y, gridBounds.width, gridBounds.height);
	rectangleGranularitySlider.setPosition(ofVec2f(rectPos.x, rectPos.y + gridBounds.getHeight() + 10));
	gridGranularitySubmit.setPosition(ofVec2f(rectPos.x, rectPos.y + gridBounds.getHeight() + 40));
	updateGridCells();
}


/**
 * set
 * Sets the position and size of the RectangularGridDragSelection
 *
 * @param rectPos: The fixed position of the RectangularGridDragSelection top left corner
 * @param rectSize: The size of the RectangularGridDragSelection
 */
void RectangularGridDragSelection::set(ofVec2f rectSize)
{
	gridBounds.set(gridBounds.x, gridBounds.y, rectSize.x, rectSize.y);
	updateGridCells();
}

void RectangularGridDragSelection::draw()
{
	// Draw the rectangular grid selection and other components
	ofDrawRectangle(gridBounds);
	rectangleGranularitySlider.draw();
	gridGranularitySubmit.draw();
}

void RectangularGridDragSelection::mouseDragged(int x, int y, int button)
{
	if (isDragging) // This means the user is currently selecting the bounds of the grid, where the width and height of the bounds grow at the same rate, so that there are always four right angles
	{
		
		float newWidth = std::abs(x - gridBounds.getX());
		float newHeight = std::abs(y - gridBounds.getY());
		float newSize = std::min(newWidth, newHeight); // Keep the shape square
		
		
		// Update gridBounds based on mouse drag
		//gridBounds.setWidth(x - gridBounds.getX());
		//gridBounds.setHeight(y - gridBounds.getY());
		gridBounds.setWidth(newSize);
		gridBounds.setHeight(newSize);
		updateGridCells(); // Update grid cells based on the new gridBounds
	}
	else
	{
		rectangleGranularitySlider.mouseDragged(x, y, button);
	}
}

void RectangularGridDragSelection::mousePressed(int x, int y, int button)
{
	if (gridBounds.inside(x, y))
	{
		// Start dragging if mouse is pressed inside gridBounds
		isDragging = true;
	}
	else if (rectangleGranularitySlider.rect.inside(x, y))
	{
		rectangleGranularitySlider.mousePressed(x, y, button);
		
		// Handle mouse press for slider and submit button
		//rectangleGranularitySlider.mousePressed(x, y, button);
		//gridGranularitySubmit.mousePressed(x, y, button);
	}
	else if (gridGranularitySubmit.rect.inside(x, y))
	{
		gridGranularitySubmit.mousePressed(x, y, button);
	}
}

void RectangularGridDragSelection::mouseReleased(int x, int y, int button)
{
	isDragging = false; // Stop dragging on mouse release
	rectangleGranularitySlider.mouseReleased(x, y, button);
	gridGranularitySubmit.mouseReleased(x, y, button);
	
	if (gridGranularitySubmit.isPressed)
	{
		//finalizeGridSetup();
	}
}

void RectangularGridDragSelection::updateGridCells()
{
	// Update gridCells based on current gridBounds and granularity
	gridCells.clear();
	float cellWidth = gridBounds.getWidth() / granularity;
	float cellHeight = gridBounds.getHeight() / granularity;
	for (float i = 0; i < granularity; ++i)
	{
		for (float j = 0; j < granularity; ++j)
		{
			float cellX = gridBounds.getX() + i * cellWidth;
			float cellY = gridBounds.getY() + j * cellHeight;
			gridCells.push_back(ofRectangle(cellX, cellY, cellWidth, cellHeight));
		}
	}
}
