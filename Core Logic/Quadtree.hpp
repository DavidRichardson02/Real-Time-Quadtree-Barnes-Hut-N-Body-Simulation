//  Quadtree.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 special most important key takeaway from the two sets of header and source files for defining the quadtree itself and
 some extraneous, but still relevant, utilities(QuadrantUtils.hpp, QuadrantUtils.cpp, Quadtree.hpp, Quadtree.cpp)
 
 
		THE BARNES-HUT METHOD FOR FORCE APPROXIMATIONS WILL ONLY REDUCE THE COMPUTATIONAL BURDEN OF RUNNING THE REAL-TIME
		N-BODY GRAVITATIONAL SIMULATION TO THE EXTENTS THAT THE QUADTREE DATA STRUCTURE IS ABLE TO ACCOMODATE THE APPROXIMATION METHODS.
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
 * The Barnes-Hut force approximation algorithm is essentially a recursive spatial-partitioning strategy
 * for grouping entities together and minimizing the number of direct entity-entity interactions, typically done 
 * by generating a single entity representative of a group of entities, then when the calculations are being 
 * done, the direct algorithm will compute each entity's interactions with every other entity, where the evolution of a given 
 * entity proceeds as directed by the cumulative affect of interactions it has with all other entities.
 *
 * Hence, while it is absolutely unavoidable that the evolution of a given entity is entirely dictated by the interactions 
 * it has with every other entity, and that the complete mathematical description of the state(motion) of an entity necessitates 
 * computing direct entity-entity interactions for all, there is no restriction for how the interactions are to be represented in the 
 * computing process. Meaning, if a group of entities can be treated as a single entity representative of the whole group, then 
 * this representative entity can stand in for the group and minimize the amount of direct entity-entity interactions, 
 * where the only consequence for approximating the entity-group as a single representative one is the loss in accuracy from using the 
 * approximation. 
 *
 *
 *
 *
 * The first step in the process of generating the quadtree is to generate global bounds for the quadtree
 * that will effectively define the area within the simulation space that the quadtree will be assigned, and
 * which must enclose all of the bodies in the simulation. 
 * 
 * The global bounds of the quadtree will accomodate all spatial subdivisions and must 
 * contain all of the n-bodies for the duration of the simulation, furthermore, the 
 * global bounds are implemented as the bounds of the root-node, meaning that at each
 * step of the simulation the entire tree will be built using these global bounds.
 * Then the process for implementing the recursive spatial-partitioning strategy 
 * can be split into three distinct phases: 
 * 			- preparation phase, initialize quadtree and prepare for bodies to be inserted
 * 			- insertion phase, pass each body into the tree and assign an enclosing node to it, subdividing as necessary to enclose  
 * 			- force calculation phase.
 * 
 * The preparation phase is responsible for ensuring the quadtree is able to accomodate the 
 * spatial-parititioning strategy(implemented in phase two), i.e., determining the bounds of
 * the space to be partitioned and initializing the quadtree with this space as the rootnode's bounds
 * such that all of the n-bodies are enclosed within, meaning, phase two can begin as soon as
 * the quadtree is ready to partition the space into quadrants bodies to be inserted into it.
 *
 *
 	STILL WORKIN ON DOCUMENTATION... WILL PICK BACK UP WITH ELABORATING ON THE THREE PHASES NEXT TIME...
 *
 *
 *
 *
 *
 *
 *
 *
 * dev NOTE: Remember that this set of header and source files(QuadrantUtils.hpp, QuadrantUtils.cpp, Quadtree.hpp, Quadtree.cpp)
 *			 are responsible for defining the quadtree such that it is able to accomodate the recursive spatial-partitioning strategy
 *			 used in the Barnes-Hut algortihm, where the basic strategy for partitioning the simulation space is 
 *			 to generate nodes(quadrants) based on the passed in body data, recursively subdividing parent nodes into quadrants 
 *			 until each subdivision contains 0 or 1 bodies.
 *
 
 * 			/// ------------ Maybe useful analogy
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
 */




			/// ------------PS Section is just an excuse for me to rant while I'm procrastinating ------------
/** PS:
 *
 *
 *
	/// ------------ Bored, partially useful rant ------------
 *	(wouldn't have been conceivable without Proffesor Alexander Brandt, with whom I have no affiliation, and his paper "On Distributed Gravitational N-Body Simulations"),
 * The larger project begins with this generic pointer-based quadtree variant of the Barnes-Hut algorithm and concludes with my real-time implementation of the Parallel Barnes-Hut 
 * Simulation(Hashed Octree in Parallel Construction with Z-Order Morton Encoding. 
 *
 * Keep in mind that this is still the two-dimensional generic pointer-based implementation of the Barnes-Hut algorithmic method for
 * approximating force calculations, and it's definitely the most straightforward of the methodologies(though it's still fairly complex, otherwise it 
 * wouldn't be worth making a whole thing about it).
 *
 *
 * My underestimation of what I was getting myself into when starting this whole thing was to the
 * extent that the Hashed-Octree, a highly specialized data structure(for me) and mostly obscure to my declared field of study, was the FIFTH data structure I ever thoroughly 
 * learned(array, vector, quadtree, octree, hashed-octree) so basically what I'm trying to say is that I spent a few months stubbornly scanning texts and picking up the stuff along
 * the way I thought would help me put together this puzzle, finding more difficulty in trying to fill in the gaps in my knowledge and correct prior misconceptions of the subject material 
 * drawn from many different and often unrelated fields, and the result is that I gained a thorough understanding of how the simulation works and the nuances found in it's implementation.
 * Furthermore, because the other variations of the BH-simulation all stem from the foundational concepts found in this variant, the complexities of these more advanced programs can be much more easily understood by examining 
 * them on the foundation of understanding gained by learning this first method for approximating force calculations, cause once you have all the pieces of the
 * puzzle they fit together very nicely without much room for confusion, just better be sure to have all the pieces and that your trying to fit them into the right place,
 * i.e., take the time to learn the fundamentals of Barnes-Hut simulations in the simple implementations so you won't be lost later on
 *
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



