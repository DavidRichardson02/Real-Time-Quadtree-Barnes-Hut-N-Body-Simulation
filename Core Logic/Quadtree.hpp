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
		/// ------------ Bored, meaningless, pretentious rant ------------
 * the only nuance going on here happens when my audacious stupidity fails to be account for the difference between my model made with a basis in things previously assumed to be
 * true now known to be false in the pursuit of achieving a description that is able to fully elaborate on a subject's nuances of interest, where the difference between a
 * completely satisfactory understanding and a seemingly satisfactory understanding are not beholden to any sort of assumed conventions, but rather that the assumed conventions
 * are designed and directed as partial truths of a whole model mapping the subject in question from observation to our brain, where all the shit(science in general tbh, for me
 * so far at least) we do is just to help in the mapping process, while the difference between our models and what we believe them to be based on are seemingly seperated by an
 * unknowable chasm between them... basically I got into Barnes-Hut simulations cause I wanted to make a sick first coding project and this was convenient cause I was also
 * hoping to relate my passion for physics/math to foster a passion for computer shit, so what I did was get in way over my head, get super lost in a rabbit hole of
 * specialized papers, tutorials, and textbooks(they are at least relevant to my degree tho, somewhat), spent a few months navigating my labyrinthine experience with N-Body
 * Simulations w/approximation methods, and basically got obsessed with N-Body simulations for a number of months, to the point that I went from learning how to check for
 * intersections between 2D circles in openframeworks and finding out what a for loop is while learning C for the first time to completing my third implementation of a simulation
 * model using the methodologies derived from the original 1986 work by Josh Barnes and Piet Hut, and the most complex one I've done to date
 *
 *
 *
	/// ------------ Bored, partially useful rant ------------
 *	(wouldn't have been conceivable without Proffesor Alexander Brandt, with whom I have no affiliation, and his paper "On Distributed Gravitational N-Body Simulations"),
 *
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
 *
 *
	/// ------------ Bored, embellishing, not useful except for me notes later rant ------------
 * but still acceptable understanding of the working models and theories this study has been chiefly concerned with, as accumulated over long periods of time by
 * reading the works of people who know much more about the subject than I do. The obstacle I ran into over and over and over again as a result of my ingenious strategy
 * to keep hitting the same wall with my head til I either forgot what the problem was, some random thing suddenly made sense after reading about it a bunch of times,
 * a stockoverflow hero, or one of my guesses ended up panning out, in any case, the only way I had a shot in at least somewhat successfully navigating this experience was to not
 * cross anything off the list of things I'm considering until I'm reasonably certain that the thing in question is not viable for the context, so over a lot of time browsing
 * articles and research papers about whatever related topic I was spending the day with my head in, a lot of fruitless and mostly baseless speculations was able to take hold,
 * very slowly at first, but as I read and learned and picked up little pieces of the puzzle, I started to build a base to make further speculations from, again and again,
 * considering the options and their implications and how those things relate to the context, and how I can put these things together to eventually end up with something
 * commendable, I have now found myself in a unique position, characterized by my recent confusing experience, and eventually, when I sat down to read some stuff about
 * obscure(to my experience) and potentially related concepts, instead of feeling dazed and confused while throwing darts at my keyboard in visualstudio(I'm embellishing cause
 * bored), I came across something that my accumulated info on Barnes–Hut simulations in general had me actually understanding what I read, understanding how it relates to my
 * program, and understanding how to change my program to reflect this new stuff. And while I did at least had the bare minimum prerequisites going in that were/are necessary for
 * understanding the idea of the model and the general concept of the approach, from a bunch of math and physics classes(I was sophemore computer engineering undergrad at start of
 * this thing), I lacked any solid intuition for understanding how to give instructions to the computer with nuance, so the months of time I spent browsing
 * mysterious papers was like me running around to a bunch of shops to see who has what I want, running around all over the place and annoying shopkeepers when I dont't know
 * what I want, but what I also did was go back to my stall, drop off what I found, why I thought it could be useful, and generally just document and update my stock as I
 * was able to interact with the works of people who spent years working out the real science of the methods and coming up with new and novel ways to perform simulations and who
 * also lay out the groundwork making any of this possible. Ergo, they were/are providing detailed accounts of their works, ergo, these super science dudes are way too smart to be
 * digestible for general audiences(in undergrad stem, or anyone interested with some relevant background I think) in a reasonable format, ergo, bonehead Dave is down the rabbit hole,
 * ergo, bonehead => Spatial Decomposition bonehead(also I haven't slept in a while so I'm in that weird sleep
 * deprived wired mindset & can't stop thinking cause atp my circadian rhythm is just boolin and whatever comes to mind is gettin typed with very little filter)
 *
 *
	/// ------------ Bored, not TLDR, pretentious(not on purpose mostly), definitely procrastination, useless  rant ------------
 * TLDR: Most people who know about how to actually do N-Body simulations are either weirdos with too much time on their hands or highly specialized experts with years of dedicated
 * experience, meaning there are no incentives for this relatively small group of people to make stuff for people being introduced to the subject matter for the first few times(can't be helped, the stuff those guys are doing is so specialized and so complex/sophisticated that the field necessitates a whole bunch of jargon to describe the full picture, which is actually undeniably a very good thing even if it makes it more difficult for , y'know, like how much less physics would Newton have discovered/pioneered if he had been concerned with making sure everybody could follow along, probably not much less, cause he was friends with guys like Leigniz anyways, but thats the point, if the researchers have to do their stuff then they shouldn't be burdened with developing models that cater any more to the human brain's capacity for misunderstanding than necessary, otherwise it defeats the whole point of developing models based on how they meet metrics dictated by us to determine usefulness, these are random notes I'll probably use when making the videos for this stuff, is anybody actually reading this, if you're reading this get dimmadome dog walked + you eat corn the long way(05/13/24 @11:36am), anyways I wanna take this opportunity to remind myself to talk about one of my favorite mathmeticians of recent history, George Box, who might be most well known for his coining of the phrase "All models are wrong, but some are useful.", which I believe to be one of the things I can treat as though it is known to be true with the most amount of certainty(noteable exceptions like 2nd law thermodynamics or anything else beyond like electromagnetism, diffEq's, or a little bit on the dimensionless constants, also like all the other stuff I'm not even qualified to mention, so this is like a meaningless thing for me to say, exceot how it's useful for me to type long rants on stuff that isn't really productive but is still more entertaining than actual work thinking), all the same, my general sentiment is that there are no correct models, and the useful ones only exist to the extents with which we are able to define observations relative to our experience with them(when it comes to understanding things independently of their relations I think it seems difficult to consider, unless it's somehow rectified, or our ineptitude explained, by the unassailable and absolute seperation that seems to lie in the path of our models accounting of the universe, the only reason apparent reason known to me from which our incentives to develop models were/are stimulated by is how they are useful to us, imagine, if there really is a model that can fully describe the universe, would you really expect it to have anything to do with a system that can only find use in models made for uses as we dictate them, does it even make sense in the first place to ask the question why?
 * does the field of statistics develop models that predict the evolution of systems because the evolution of systems develops with a rich historical precedence, which is used by our minds to develop models mapping these events to ones we expect to proceed them based on what has come before, how, and the enviroment/conditions when they did, that must always be by-and-large designed on a case-by-case basis, or do they hint at a path to a more absolute truth, or perhaps a better description of such events. Don't we seem to assume that the world around us is obligated to act how our models tell us to, isn't it just that by cross-referencing these models and checking them for failure in every way we can think of will never deliver us to a satisfactory answer with regards to , but rather only stimulate our growth towards understanding how exactly we are a product of our enviroment, as these models are adjusted(versatile models specialized for some purpose like what famously happened to Einstein's equations with diverse and myriad discoveries that followed by exploring many specific cases for the equations to examine, making great progress but also uncovering mysteries we might have otherwise never imagined, although not necessarily wrong) <-- I'm talking specifically the singularity black hole thing, I would never diss Einstein in any way the #2 goat of science in human history> to find use in whatever purpose their modeler had in mind, one that the original modeler, and model, might not have inconceivably failed to account for.
 * On an actual serious note though, all of this weird talk is like 90% baseless speculation, and regardless of whether every word of it is right or not one, it still really doesn't move the goal posts a whole lot, and there's a whole bunch of unbelievable science out there that I've had the privilige of interacting with to the point it seems very clear to me that there's a whole lotta stuff we'll almost certainly never have the chance to explore, but as the species grows over time(talkin bout technology stuff), we'll probably find some pretty crazy stuff, and that some of our stuff is pretty crazy, but only the people who stick around to push that stuff forward will get to experience what that's like, assuming we don't blow each other up or somthing, so seeing as how I basically spent a while gathering up all the stuff you would need to build a simulation, I might as well put it all together in a compendium as some sort of digestible and comprehensive format to spread this stuff to more people who can experience it.
 *
 *
 *
 *
 *
 * Basically my overarching goal with this directed study is to take the stuff I know, branch it to the real information+jargon dense research/texts, and then branch that version
 * to the stuff most people with a solid math/physics model can explore in a comprehensive format guiding users from the lots of really simple shit and how that builds up to the
 * rigorous cool shit, cause the hard stuff is actually just lots of easy stuff stacked up, and when it comes to N-Body simulations w/approximation algortihms I have an advantage
 * over the experts when it comes to teaching, see because their experts they know(or knew) more basic stuff like this for probably long enough to forget all the stupid
 * misconceptions they might ran into or seen coming and avoided, so it's easier for me to see where the pitfalls are, the flip side of this is that their expert perspective
 * and model has to view the smaller building block stuff as rigid and assumed as knowns, otherwise they wouldn't be able to do the crazy shit that pushes fields forward,
 * cause it's just that rigorous the situation demands that sort of thing, like imagine if every time you did algebra you had to check a ~250 long dissertation that sets up
 * and proves the math for 1+1=2(plz don't get mad at this lackluster analogy if your a mathmetician, I hope it pissed you off if your a paleontologist, what are you even
 * doing here?), any system has to rely on assumed knowns like these, and that really has literally nothing to do with what I started typing this out for, but atp idk bruh
 * whatever, maybe like one dude is gonna read this if I get unlucky.
 *
 *
 *
 *
		/// ------------ THE REAL TLDR ------------
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



