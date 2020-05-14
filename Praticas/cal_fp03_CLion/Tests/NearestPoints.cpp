/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

ostream &operator<<(ostream &out, Result res) {
    out << "From " << res.p1 << " to " << res.p2 << " - Distance: " << res.dmin;
    return out;
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;
	double dist;
	for (int i = 0; i < vp.size(); i++) {
	    for (int j = 0; j < vp.size(); j++) {
	        if (vp[i] == vp[j]) continue;
	        dist = vp[i].distance(vp[j]);
	        if (dist < res.dmin) {
	            res.dmin = dist;
	            res.p1 = vp[i];
	            res.p2 = vp[j];
	        }
	    }
	}
    cout << endl << res << endl << endl;
	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);
	// TODO
	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
	// TODO
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> vp, int left, int right, int numThreads) {
	Result res;
    int usedSize = abs(left-right) + 1;
    // Base case of two points
	// TODO
    if (usedSize == 2) {
        res.p1 = vp[0];
        res.p2 = vp[1];
        res.dmin = vp[0].distance(vp[1]);
        return res;
    }

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	// TODO
	if (usedSize == 1) {
	    return Result();
	}

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	// TODO
    int midIx = (left + right)/2;
	Result lRes, rRes;
    if (numThreads > 1) {
        std::thread t([&](){ lRes = np_DC(vp, left, midIx-1, numThreads/2); });
        rRes = np_DC(vp, midIx, right, numThreads/2);
        t.join();
    }
//    else {
        lRes = np_DC(vp, left, midIx-1, numThreads);
        rRes = np_DC(vp, midIx, right, numThreads);
//    }


	// Select the best solution from left and right
	// TODO
	if (lRes.dmin < rRes.dmin) res = lRes;
	else res = rRes;

	// Determine the strip area around middle point
	// TODO
	int ixBegStrip, ixEndStrip;
	bool done;
	for (int i = 1; i < vp.size(); i++) {
        done = true;
        if (vp[midIx + i].distance(vp[midIx]) < res.dmin) { ixEndStrip = midIx + i; done = false; }
        if (vp[midIx - i].distance(vp[midIx]) < res.dmin) { ixBegStrip = midIx - i; done = false; }
	    if (done) break;
	}

	int numPointsInStrip = ixEndStrip - ixBegStrip;

    for(int i = 0; i < numPointsInStrip; i++ )
        for(int j = i + 1; j < numPointsInStrip; j++ )
            if( vp[i].distance(vp[j]) < res.dmin ) {
                res.p1 = vp[i];
                res.p2 = vp[j];
                res.dmin = vp[i].distance(vp[j]);
            }

	// Order points in strip area by Y coordinate
	// TODO


	// Calculate nearest points in strip area (using npByY function)
	// TODO

	// Reorder points in strip area back by X coordinate
	//TODO

	return res;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
    Result res = np_DC(vp, 0, vp.size() - 1, numThreads);
    cout << endl << res << endl << endl;
    return res;
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	Result res = np_DC(vp, 0, vp.size() - 1, numThreads);
	cout << endl << res << endl << endl;
	return res;
}
