/*
 * BVH.cpp
 *
 *
 */
#include "BVH.h"
#include "queue"

namespace rt{

	BVH::BVH(std::vector<Shape*> shapes):shapes(shapes)
	{
		printf("Building BVH \n");

		std::vector<BoundingBox*> bbs;

		// First puts every shape in the scene in a Bounding Box(AABB)
		for (std::vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); ++iter)
		{			
			Shape* shape = *iter;
			std::vector<Shape*> bbShapes;

			bbShapes.push_back(shape);
			bbs.push_back(new BoundingBox(bbShapes));
		}


		// Builds the tree out of these AABBs and stores the root node
		root = buildTree(bbs);

		printf("BVH has been built \n");

	}

	// builds the BVH tree recursively
	BoundingBox* BVH::buildTree(std::vector<BoundingBox*> bbs)
	{

		// if there are onlz one AABB left in the list -> that is the root
		if(bbs.size() == 1)
		{
			return bbs[0];
		}

		int indexes[2] = {0,0};
		int i = 0,j =0;
		float distance = INFINITY;

		// Finds the two closest AABB
		for (std::vector<BoundingBox*>::iterator iter1 = bbs.begin(); iter1 != bbs.end(); ++iter1)
		{			
			BoundingBox* bbsI = *iter1;
			
			for (std::vector<BoundingBox*>::iterator iter2 = bbs.begin(); iter2 != bbs.end(); ++iter2)
			{			
				BoundingBox* bbsJ = *iter2;

				if(i != j && ((bbsI -> getCenter() - bbsJ-> getCenter()).length()) < distance)
				{
					indexes[0] = i;
					indexes[1] = j;
					distance = (bbsI -> getCenter() - bbsJ-> getCenter()).length();
				}
				j++;
				
			}
			j = 0;
			i++;
		}

		std::vector<Shape*> bb;
		bb.push_back(bbs[indexes[0]]);
		bb.push_back(bbs[indexes[1]]);

		//Removes them from the list by removing the bigger index first so it will not shift
		if(indexes[0] > indexes[1])
		{
			bbs.erase(bbs.begin()+indexes[0]);
			bbs.erase(bbs.begin()+indexes[1]);
		}
		else
		{
			bbs.erase(bbs.begin()+indexes[1]);
			bbs.erase(bbs.begin()+indexes[0]);
		}

		// Builds a new box out of the two closest shapes and adds it to the list
		BoundingBox* box = new BoundingBox(bb);
		bbs.push_back(box);

		// repeats until only 1 box remains in the list
		return buildTree(bbs);
	}

	BVH::~BVH()
	{}

	Hit BVH::intersect(Ray ray)
	{
		Hit h;
		Hit curHit;
		std::queue<Shape*> queue;
		std::vector<Shape*> v;
		Shape* curShape;

		curHit = root-> intersect(ray);

		// Checks if the ray intersets the root node
		// if it does not intersect -> return false hit
		if(curHit.intersected == false)
		{
			return curHit;
		}

		 v = root -> getShapes();

		 //if it does observes if root was a leaf
		if(curHit.shape -> isLeaf() == true)
		{
			// if it was returns shape intersection
			return v[0] -> intersect(ray);
		}

		// otherwise extracts the AABBs from the root and adds them to the queue
		queue.push(v[0]);
		queue.push(v[1]);

		// queue rotates through the AABBs using breath first search
		while(!queue.empty())
		{
			curShape = queue.front();
			queue.pop();

			curHit = curShape -> intersect(ray);

			// if the ray hits the AABB
			if(curHit.intersected == true)
			{

				v = curHit.shape -> getShapes();

				// if the AABB is a leaf return shape intersection
				if(curHit.shape -> isLeaf() == true)
				{
					curHit = v[0] -> intersect(ray);
					if(curHit.intersected == true && curHit.distance < h.distance)
					{
						h = curHit;
					}
				}
				// if not extract the AABBs from the box and add them to the queue
				else
				{
					queue.push(v[0]);
					queue.push(v[1]);
				}
			}
			// otherwise discard AABB
		}


		return h;
	}



} //namespace rt


