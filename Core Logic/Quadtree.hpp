//  Quadtree.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 special most important key takeaway from the two sets of header and source files for defining the quadtree itself and
 some extraneous, but still relevant, utilities(QuadrantUtils.hpp, QuadrantUtils.cpp, Quadtree.hpp, Quadtree.cpp)
 
 
		THE BARNES-HUT METHOD FOR FORCE APPROXIMATIONS WILL ONLY REDUCE THE COMPUTATIONAL BURDEN OF RUNNING THE REAL-TIME
		N-BODY GRAVITATIONAL SIMULATION TO THE EXTENTS THAT THE QUADTREE DATA STRUCTURE IS ABLE TO ACCOMODATE IT.
 */


/**
 * Quadtree Class: Efficient spatial partitioning for N-Body simulation.
 *
 *
 * The Quadtree class provides an efficient mechanism for spatial partitioning of bodies
 * in the Barnes-Hut algorithm. It subdivides a region into four quadrants and recursively
 * stores the bodies into the appropriate quadrant.
 * This helps in approximating the gravitational force calculations between the N-bodies,
 * effectively reducing computational complexity from O(N^2) to O(NlogN).
 *
 *
 *
 * dev NOTE: Remember that this set of header and source files(QuadrantUtils.hpp, QuadrantUtils.cpp, Quadtree.hpp, Quadtree.cpp), 
 *			 only exist to define the data structure that is the quadtree which this simulation will use to partition space
 *			 for implementing the Barnes-Hut algorithm for approximating force calculations.
 *
 * 			/// ------------ Ambiguous but potentially insightful analogy
 *				If the simulation is likened to a process where we plant a tree, water it, and guide it's development, which culminates with a harvest of apples,
 *				then the files defining the quadtree data structure are where we come up with the coding for the appletree's DNA, which will dictate the development process...,
 *				|
 *				|
 *				V
 *				while the files where the tree(s) is(are) built and the force calculations approximated are like the phases in the appletree's development which
 *				provide stimuli to further development
 *
 *				|
 *				|
 *				V
 *				then like the appletree guy waters the appletrees, cuts off dead branches, and keeps insects away to foster an enviroment
 *				conducive to the trees growth, a minimal amount of losses, and ensure a quality harvest of apples,
 *
 *
 *				|
 *				V
 *				we then provide stimuli to this quadtree to grow by inserting bodies into it, pruning empty nodes, and minimizing bugs in order to provide an enviroment for the
 *				simulation to facilitate an architecture tailored for scalable N-Body Barnes-Hut gravitational systems, minimal amount of overhead from the tree's descendants
 *				and their elements, a minimal amount of direct force calculations(dfc's are mostly a seperate concern from tree memory stuff tho, still though the issue of dfcs is inextricable from the tree as long as we intend to avoid the direct method's O(N^2) computational complexity of force calculations, which is basically big big slow, exponentially slower for greater N too, so like the force approximations can only help the performance to the extents that the quadtree is able to accomodate such methodolgies),
 *				towards achieving a simulation characterized by a high level of accuracy for force calculations(see benchmarking mode... still just in paper notes as of 05/13 @9am).
 *
 *
 *
 *
 * 			/// ------------ Another ambiguous but potentially insightful analogy
 *			Expressed as an analogy, these files defining the quadtree data structure might be likened to being as to the
 *			files where the quadtree is built and the files where the force calculations are made
 *			as a complex recipe for a meal would be compared to the restaurant where the meal is cooked.
 *
 *			The careful recipe(quadtree data structure) and sophisticated ingredients(entities partitioned for... see quadtree note below) respectively serve as the
 *			blueprints dictating the preparation process of the meal and the foundation upon which the meal must stand in it's execution,
 *			both of which will be key in determining the quality of the meal, where the only acceptable result is achieved by the harmonious and nuanced direction(s) of the recipe
 *			being carried out using reliable ingredients as a foundation.
 *
 *			Here we outline our rigorous methodologies, later we cook. 
 *
 *
 */




			/// ------------PS Section is just an excuse for me to rant while I'm procrastinating ------------
/** PS:
 *
 * The only aspect the TLDR analogy falls flat on it's face and fails to account for, with regards to the: abstract, ambiguous, and arbitrairly conceptulized
 * relations drawn between the two, from actual simulation is that once we start the cooking process(run the simulation), it will be too late
 * to change the recipe, meaning our model has to be able to account for all reasonable variability... ideally at least, the computer is gonna do whatever the
 * hell the computer tells it to do, and at the level in the language command chain
 * (how it looks to me: existential crisis gibberish-->slightly less gibberish-->assembly-->C/C++-->bastard snake)
 * that we are submitting instructions from, it's basically just a bunch of educated guesses with priority placed on just minimizing silly shit by meticulously documenting
 * everything and getting the little shit right in order to hopefully avoid all the little pitfalls that my ignorance leaves me blind to(once you go below C that shit might as well be Latin for all the difference it would do me, besides this sort of thing is pretty much a non-issue for a project like this, whose scope will have no problem finding a complete description drawn within the confines of existing mathmetically well-defined computer limitations, and is unlikely to approach the fringe edge of any field except potentially one based in educational pursuits, which is more focused on teaching tools based on da code, not just da code, 
 *
 *
 *
 *
	/// ------------ Bored, partially useful rant ------------
 *	(wouldn't have been conceivable without Proffesor Alexander Brandt, with whom I have no affiliation, and his paper "On Distributed Gravitational N-Body Simulations"),
 * which was my real-time implementation of the Parallel Barnes-Hut Simulation(Hashed Octree in Parallel Construction with Z-Order Morton Encoding over a period of around 5
 * months, which might sound impressive if you don't know the details, but my underestimation of what I was getting myself into when starting this whole thing was to the
 * extent that the Hashed-Octree, a highly specialized data structure(for me) and mostly obscure to my field of study(but just in the sense that I'm not gonna be doing N-Body
 * simulation for a living, as a learning experience it has been invaluable), was the SECOND data structure I ever thoroughly learned, the first being the pointer-based
 * quadtree(which I'm pretty sure I did wrong the first time, also remember this is still the generic pointer-based implementation of the Barnes-Hut algorithmic method for
 * approximating force calculations, and it's in 2D, and it's definitely the most straightforward of the methodologies, not a knock, it's still very complex, otherwise it wouldn't be worth making a whole thing about it, or maybe it's difficulty comes more from how it draws from many different and often unrelated fields, cause once you have all the pieces of the puzzle they fit together very nicely without much room for confusion, just better be sure to have all the pieces and that your trying to fit them into the right frame, which I found to be a tedious process) so basically what I'm trying to say is that I
 * spent a few months stubbornly scanning texts and picking up the stuff along the way I thought would help me put together this puzzle, and the result is that I
 * gained a limited(I'd say I know very thoroughly how the simulation works, while I think the why question in the nuances of the process will always be ongoing for me, reason
 * being the correct simulation approximation method is just defined as the one our current models can most thoroughly account for with regards to the evolution of the chaotic
 * dynamical system(i.e., the N-body -> N^2 interactions part... more bodies->more terms exponentially in a diffyQ thing->more unpredictable->whole buncha new shit like chaos
 * theory and dynamical systems came about after Sir Isaac Newton discovered the phenomenon, hence the lack any general analytical solutions, and one piece of the great incentive for simulation)

 *
		/// ------------ TLDR ------------
 *
 *		Summary: 
 *			- N-Body simulations usually only accessible through a diligent accumulation of years of study,
 *
 *		Why Thing: 
 *			- I got in way over my head and spent months of time floundering when I could have been working on a more reasonable project for a beginner
 *
 *		Why Matter: 
 *			- Though I was largely in the dark regarding any the issuance of instructions to the computer with any nuance
 *			- Too late to backout, only thing to do is either follow through or fail, so I failed to meaningfully make progress, did that frequently for a while, til I did it less,
 *			  then not so often, now I'm in the follow through phase for the most part
 *			- Because I did not act with the patience to build a thorough network of understanding and carefully approach this topic after accumulating years of experience with
 *			  relevant subject matter, I had to amend this by spending months untangling the intricacies of various algorithms, data structures, and physical phenomena, only to
 *			  find that I had more questions than answers and feeling like I was doing more legwork trying to figure out where to start than actually diving deep into the subject.
 *
 *		SHOULD YOU CARE? ¯\_(ツ)_/¯
 *			- Well I figure there's probably a few type of people who might be interested in this sort of thing, like experts for fun/supervision,
 *			  people who aren't really interested in doing the whole thing but want to participate for their own reasons(maybe they just wanna check it out not jump into the pool
 *			  all at once), students that wanna make something cool, and the rest of my target audience can just be lumped up in "hey what's that weird lookin thing over there" if
 *			  they look into this project.
 *			- So if your a student who wants to make something cool, or just interested in hearing what I learned, your probably my target viewer audience, for whom my goal is
 *			  singular, provide the resources to equip you with the tools to make B.H. sim's and make readily available the resources instructing how to craft with them as well as
 *			  why, ideally providing an elaboration drawing from all three of these important aspects of B.H. simulations
 *
 *
 *
 * Basically when I get in over my head with some recent obsession and don't wanna take my time to build a foundation of the basics leading up to it and I try to draw an understanding of the obscure thing by mapping what I know to what I want to know about and then just trying to fill in the gaps left by my ignorance by hopping over to whatever paper I was reading or one of it's refrecnes, I just typed it out like that cause I'm distracting myself and I'm feeling pretentious and should get back to work)
 *
 *
 */


#pragma once
#include "Vects.hpp"
#include "Geometry.hpp"
#include "CoordinateSystem.hpp"
#include "StatisticalMethods.hpp"
#include "DrawingUtilities.hpp"
#include "SequenceContainers.hpp"
#include "ObjectPool.hpp"
#include "SimulationEntities.hpp"
#include "QuadrantUtils.hpp"
#include "ofMain.h"


#include <unordered_set>
#include <algorithm>  // for std::find





const float maxDepth = 14; // Barnes-Hut approximation parameter

class Quadtree
{
public:
	// ------------- Constructors and Destructor -------------
	Quadtree();
	Quadtree(const Quadtree* other);
	Quadtree(ofRectangle& nodeBounds, QuadrantEnum quadrant, int depthLevel, float nodeMass, ofVec2f& nodeCOM);
	Quadtree(ofRectangle& nodeBounds, QuadrantEnum quadrant);
	~Quadtree();
	
	
	// ------------- Spatial Operations -------------
	void insert(Body *& body); // Inserts a body into the Quadtree.
	void computeTreeMassDistribution();
	void pruneNode(Quadtree* &treeNode); //Recursively free this treeNode and all of its children.
	void pruneEmptyNodes(Quadtree* &treeNode);
	
	
	// ------------- Node Operations -------------
	void resetNode(Quadtree *&treeNode); // Resets a specific node for reuse.
	void draw(); // Visualization method for debugging and representation.
	void printTree();
	
	
	
	// ------------- Member Variables(Tree Parameters) -------------
	ofRectangle bounds; // Bounding box for this quadtree node.
	
	/** \brief Data for the body.
	 Only valid if this is a leaf node.
	 */
	Body *nodeBody;
	
	std::array<Quadtree*, 4> children; // Child nodes.
	int depth; // Depth level of the node.
	ofVec2f centerOfMass; // Center of mass of all bodies in this node.
	float totalMass; // Combined mass of all bodies in this node.
	bool hasChildren; // Flag indicating the presence of children.
	int bodyCount; // Number of bodies in this node.
};








static inline void TestBuildQuadtree(Quadtree* &rootNode, std::vector<Body *> &bodies, ObjectPool<Body> &bodyPool);
static inline void BuildQuadtree(Quadtree* &rootNode,  std::vector<Body *> &bodies, ObjectPool<Body> &bodyPool);
static inline void ComputeQuadtreeMassDistribution(Quadtree* &rootNode);//compute the barycenters/center of masses of all nodes in tree
static inline void PruneEmptyNodesFromTree(Quadtree* &rootNode); //prune the empty nodes from the quadtree
static inline void ResetTree(Quadtree* &rootNode);//reset all nodes in tree nodes except the root node












static inline void TestBuildQuadtree(Quadtree* &rootNode, std::vector<Body *> &bodies, ObjectPool<Body> &bodyPool)
{
	rootNode = new Quadtree();  // Create a new Quadtree and have rootQuadtree point to it
	rootNode->bounds.set(-250000, -250000, 500000, 500000);
	
	
	for (size_t i = 0; i < bodies.size(); i++)
	{
		if(bodies[i] != nullptr && bodies[i]->mass != 0)
		{
			rootNode->insert(bodies[i]);
		}
		else
		{
			ReleaseObjectFromPool(bodyPool, bodies, i);
			bodies.erase(bodies.begin() + i);
			cout<<"\n\nBody insertion failed, either nullptr or mass == 0\n\n" << endl;
		}
	}
	
	cout<<"Tree Constructed ofGetElapsedTimef(): " << ofGetElapsedTimef();
	
	
	PruneEmptyNodesFromTree(rootNode);
	ComputeQuadtreeMassDistribution(rootNode);
	
	
	cout<<"\n\n Tree Complete ofGetElapsedTimef(): " << ofGetElapsedTimef();
}


static inline void BuildQuadtree(Quadtree* &rootNode, std::vector<Body *> &bodies, ObjectPool<Body> &bodyPool)
{
	rootNode = new Quadtree();  // Create a new Quadtree and have rootQuadtree point to it
	rootNode->bounds.set(-250000, -250000, 500000, 500000);
	
	
	for (size_t i = 0; i < bodies.size(); i++)
	{
		rootNode->insert(bodies[i]);
		
	}
	
	
	PruneEmptyNodesFromTree(rootNode);
	ComputeQuadtreeMassDistribution(rootNode);
}




static inline void ComputeQuadtreeMassDistribution(Quadtree* &rootNode)
{
	rootNode->computeTreeMassDistribution();
}




static inline void PruneEmptyNodesFromTree(Quadtree* &rootNode)
{
	int mostDepth = 0;
	rootNode->pruneEmptyNodes(rootNode);
}




static inline void ResetTree(Quadtree* &rootNode) //reset and delete all nodes except the root node
{
	if (rootNode->hasChildren)
	{
		for (auto& child : rootNode->children)
		{
			if (child != nullptr)
			{
				rootNode->resetNode(child);
			}
		}
	}
}
































/**
 dev NOTE: the stuff past this point is experimental and not relevant to the generic pointer based quadtree implementation for approximating force calculations, also it's
 not yet implemented for my 2D simulations
 
 
 PS: 3D just has more complexities in general, the three functions below are me trying to map somebody else's novel solution to my own work,
     namely, Proffesor Alexander Brandt Department of Computer Science University of Western Ontario London, with whom I have no affiliation(except his work is the reason for my study, mainly his 2022 paper "On Distributed Gravitational N-Body Simulations"
 */



static inline int BarnesHutMAC(Quadtree* &node, ofVec2f bodyPosition, float theta);
static inline void ComputeQuadTreeForce(Quadtree* &rootNode, std::vector<Body*> &bodies, ofVec2f* &bodiesAccelerations, float G, float theta);
static inline int TraverseInteractionList(Quadtree* &rootNode, ofVec2f bodyPosition, ofVec2f &bodiesAccelerations, Quadtree** &walkList, Quadtree** &interactList, float G, float theta);
static inline int ComputeForceInteractionList(Body *&body, ofVec2f &bodiesAccelerations, Quadtree** &interactList, int listLength);



inline int BarnesHutMAC(Quadtree* &node, ofVec2f bodyPosition, float theta)
{
	// node's diamater / distance-to-bodyPosition < theta
	ofVec2f distance = node->centerOfMass - bodyPosition;
	
	float distSquared = distance.x * distance.x + distance.y * distance.y;
	
	return(4.0 * node->bounds.width * node->bounds.width < distSquared * theta * theta);
	
	
}



