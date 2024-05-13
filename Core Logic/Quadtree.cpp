//  Quadtree.cpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02


#include "Quadtree.hpp"
#include "ofMain.h"
using namespace std;






Quadtree::Quadtree()
{
	bounds = ofRectangle();
	centerOfMass.set(0, 0);
	totalMass = 0;
	hasChildren = false;
	bodyCount = 0;
	depth = 0;
	nodeBody = nullptr;
	
	children[0] = nullptr;
	children[1] = nullptr;
	children[2] = nullptr;
	children[3] = nullptr;
}

Quadtree::Quadtree(const Quadtree* other)
{
	bounds = other->bounds;
	nodeBody = other->nodeBody;
	depth = other->depth;
	totalMass = other->totalMass;
	centerOfMass = other->centerOfMass;
	bodyCount = other->bodyCount;
	hasChildren = other->hasChildren;
	
	children[0] = other->children[0];
	children[1] = other->children[1];
	children[2] = other->children[2];
	children[3] = other->children[3];
}



Quadtree::Quadtree(ofRectangle& nodeBounds, QuadrantEnum quadrant, int depthLevel, float nodeMass, ofVec2f& nodeCOM)
{
	float halfWidth = nodeBounds.width * 0.5;
	bounds.width = halfWidth;
	bounds.height = halfWidth;
	
	ofVec2f quadrantDirection = DetermineQuadrantDirection(quadrant);
	bounds.x = nodeBounds.x + quadrantDirection.x * halfWidth;
	bounds.y = nodeBounds.y + quadrantDirection.y * halfWidth;
	
	
	bodyCount = 0;
	totalMass = nodeMass;
	centerOfMass = nodeCOM;
	nodeBody = nullptr;
	depth = depthLevel;
	
	
	hasChildren = false;
	children[0] = nullptr;
	children[1] = nullptr;
	children[2] = nullptr;
	children[3] = nullptr;
}


Quadtree::Quadtree(ofRectangle& nodeBounds, QuadrantEnum quadrant)
{
	float halfWidth = nodeBounds.width * 0.5;
	bounds.width = halfWidth;
	bounds.height = halfWidth;
	
	ofVec2f quadrantDirection = DetermineQuadrantDirection(quadrant) * 0.5;
	//bounds.x = nodeBounds.x + quadrantDirection.x * halfWidth;
	//bounds.y = nodeBounds.y + quadrantDirection.y * halfWidth;
	ofVec2f boundsTopLeft = ofVec2f(nodeBounds.x, nodeBounds.y) + quadrantDirection * halfWidth;
	
	bounds.x = boundsTopLeft.x;
	bounds.y = boundsTopLeft.y;
	
	//
	/*
	 if (quadrant == 0)  //NW quad
	 {
	 bounds.x = nodeBounds.x;
	 bounds.y = nodeBounds.y;
	 }
	 if (quadrant == 1)  //NE quad
	 {
	 bounds.x = nodeBounds.x + halfWidth;
	 bounds.y = nodeBounds.y;
	 }
	 if (quadrant == 2)  //SW quad
	 {
	 bounds.x = nodeBounds.x;
	 bounds.y = nodeBounds.y + halfWidth;
	 }
	 if (quadrant == 3)  //SE quad
	 {
	 bounds.x = nodeBounds.x + halfWidth;
	 bounds.y = nodeBounds.y + halfWidth;
	 }
	 //*/
	
	bodyCount = 0;
	totalMass = 0;
	centerOfMass.set(0,0);
	
	nodeBody = nullptr;
	hasChildren = false;
	
	children[0] = nullptr;
	children[1] = nullptr;
	children[2] = nullptr;
	children[3] = nullptr;
}



Quadtree::~Quadtree()
{
	bounds = ofRectangle();
	centerOfMass.set(0, 0);
	totalMass = 0;
	hasChildren = false;
	bodyCount = 0;
	depth = 0;
	nodeBody = nullptr;
	
	
	delete children[0];
	delete children[1];
	delete children[2];
	delete children[3];
}


void Quadtree::insert(Body *& body)
{
	//if(body == nullptr)
	//{
	//     return;
	//}
	//if(bounds.width < body->mass) // Only insert the body if it fits within the bounds of the node
	//{
	
	//cout<<"\n\nBody insertion failed, node bounds could not enclose body";
	//cout<<"\nbounds.width: " << bounds.width;
	//cout << "    \nBounds Position: (" << bounds.x; cout << ", " << bounds.y; cout << ")";
	
	
	//cout << "    \n\nBody Position: (" << body->position.x; cout << ", " << body->position.y; cout << ")";
	//cout << "    \nBody Mass: " << body->mass << endl << endl << endl;
	
	//return;
	//}
	
	
	
	if(bodyCount > 1)
	{
		QuadrantEnum quad = DetermineQuadrant(bounds, body->position);
		
		
		if (children[quad] == nullptr)
		{
			children[quad] = new Quadtree(bounds, quad, depth + 1, body->mass, body->position);
		}
		children[quad]->insert(body);
		
		bodyCount = bodyCount + 1;
		totalMass += body->mass;
		hasChildren = true;
	}
	else if(bodyCount == 1)
	{
		QuadrantEnum quad = DetermineQuadrant(bounds, nodeBody->position);
		
		if (children[quad] == nullptr) //check if child node containing the body exists, if not, create it
		{
			children[quad] = new Quadtree(bounds, quad, depth + 1, body->mass, body->position);
		}
		children[quad]->insert(nodeBody);
		
		
		
		
		quad = DetermineQuadrant(bounds, body->position);
		if(children[quad] == nullptr) //check if child node containing the body exists, if not, create it
		{
			children[quad] = new Quadtree(bounds, quad, depth + 1, body->mass, body->position);
		}
		children[quad]->insert(body);
		
		
		bodyCount = bodyCount + 1;
		totalMass += body->mass;
		hasChildren = true;
	}
	else if(bodyCount == 0)
	{
		nodeBody = body;
		bodyCount = 1;
	}
}


void Quadtree::computeTreeMassDistribution()
{
	if (bodyCount == 0)
	{
		totalMass = 0;
		centerOfMass.set(0, 0);
		return;
	}
	
	if (bodyCount == 1)
	{
		centerOfMass = nodeBody->position;
		totalMass = nodeBody->mass;
	}
	else if (hasChildren || bodyCount > 1)
	{
		ofVec2f tempCOM(0.0, 0.0);
		totalMass = 0;
		
		for (int i = 0; i < 4; ++i)
		{
			if (children[i] && children[i]->bodyCount > 0)
			{
				children[i]->computeTreeMassDistribution();
				
				totalMass += children[i]->totalMass;
				tempCOM +=  children[i]->centerOfMass * children[i]->totalMass;
			}
		}
		centerOfMass = tempCOM / totalMass;
	}
}
void Quadtree::pruneNode(Quadtree* &treeNode)
{
	if(treeNode)
	{
		if (treeNode->hasChildren)
		{
			for(int i = 0; i < 4; ++i)
			{
				pruneNode(treeNode->children[i]);
				
				//if(treeNode->children[i] != nullptr)
				//{
				//	delete treeNode->children[i];
				//}
			}
			
			
			delete treeNode->children[0];
			delete treeNode->children[1];
			delete treeNode->children[2];
			delete treeNode->children[3];
			
			delete treeNode;
		}
	}
}

void Quadtree::pruneEmptyNodes(Quadtree* &treeNode)
{
	if(treeNode == nullptr)
	{
		return;
	}
	
	int nullCount = 0;
	
	// Iterate over all possible child nodes
	for (int i = 0; i < 4; ++i)
	{
		if(treeNode->children[i] == nullptr)
		{
			nullCount++;
		}
		else if (treeNode->children[i]->bodyCount == 0)
		{
			pruneNode(treeNode->children[i]);
			nullCount++;
		}
		else //the child exists and it has at least one body contained within it
		{
			// Recursively prune children of this child node
			pruneEmptyNodes(treeNode->children[i]);
		}
	}
	
	if (nullCount == 4) //Check if all children node's are nullptr while
	{
		pruneNode(treeNode);// Release the node's memory
	}
}


void Quadtree::resetNode(Quadtree *&treeNode)
{
	if(treeNode)
	{
		treeNode->bounds = ofRectangle();
		treeNode->centerOfMass.set(0, 0);
		treeNode->totalMass = 0;
		treeNode->hasChildren = false;
		treeNode->bodyCount = 0;
		treeNode->depth = 0;
		treeNode->nodeBody = nullptr;
		
		delete treeNode;
		delete treeNode->children[0];
		delete treeNode->children[1];
		delete treeNode->children[2];
		delete treeNode->children[3];
	}
	treeNode = nullptr;
}



void Quadtree::draw()
{
	if (hasChildren)
	{
		for (int i=0; i<4;i++)
		{
			if (children[i] != nullptr)
			{
				children[i]->draw();
			}
		}
	}
	
	ofNoFill();
	ofSetLineWidth(0.75);
	ofSetColor(255, 255, 255, 96.75);
	ofDrawRectangle(bounds);  // draw the bounding box of the node
	
}




void Quadtree:: printTree()
{
	cout << "\n\n\n\n\nnodeBounds.size: " << bounds.width;
	cout << "\nnodeBounds.center: (" << bounds.x;  cout << ", " << bounds.y; cout << " )";
	
	
	cout << "\ntotalMass: " << totalMass;
	cout << "\ncenterOfMass: (" << centerOfMass.x;  cout << ", " << centerOfMass.y; cout << " )";
	
	
	cout << "\n\nNode Depth: " << depth;
	cout << "\nbodyCount: " << bodyCount;
	if(nodeBody)
	{
		cout << "\nNode Quadrant: " << DetermineQuadrant(bounds, nodeBody->position);
		
		
		cout << "\n\nnodeBody.mass: " << nodeBody->mass;
		cout << "\nnodeBody.position: (" << nodeBody->position.x;  cout << ", " << nodeBody->position.y; cout << " )";
		cout << "\nnodeBody.velocity: (" << nodeBody->velocity.x;  cout << ", " << nodeBody->velocity.y; cout << " )";
	}
	cout << "\n\n\n\n";
	
	
	for (int i=0 ;i<4;i++)
	{
		if (children[i] != nullptr)
		{
			children[i]->printTree();
		}
	}
}
