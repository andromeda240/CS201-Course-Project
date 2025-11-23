#include <iostream>
using namespace std;

/*To do
~~~ done ~~~ Structure to make a point in k dim space as a node
~~~ done ~~~ Insertion 
Randomly built kd tree
~~~ done ~~~ Searching (exact match queries)
Insertion query 
~~~ done ~~~ Exact match query (basically search)
Partial match query
~~~ done ~~~ Region query
    - in region
    - found
    - bounds intersect region
NN match query
Deletion 
Optimal tree
Application 
Area of further research~~ 
extra: radius query, bounding box
*/

const int k = 2;

// structure of a node in k-d tree
struct node
{
    int point[k];
    node *left, *right;
};


// to check if two points are same
bool arePointsSame (int point1[], int point2[]){
    for(int i = 0; i < k; i++){
        if(point1[i] != point2[i]) return false;
    }
    return true;
}

// function to create nodes (return type -> node)
node* createNode(int arr[])
{
    node* temp = new node;

    for(int i = 0; i < k; i++)
        temp->point[i] = arr[i];

    temp -> left = temp -> right = NULL;
    return temp;
}

// recursive function for insertion
node* insertRecursive(node* root, int point[], unsigned depth){

    if(root == NULL) 
        return createNode(point);

    if(arePointsSame(root->point, point))
        return root;
    
    unsigned cd = depth % k; //cd is the abbreviation for current dimension

    if(point[cd] < (root -> point[cd]))
        root -> left = insertRecursive(root -> left, point, depth + 1);
    else
        root -> right = insertRecursive(root -> right, point, depth+1);

    return root;
}

// function to insert a point(k dimensional array) in the tree
node* insert(node* root, int point[]){
    return insertRecursive(root, point, 0);
}

// recursive function for search
bool searchRecursive(node* root, int point[], unsigned depth){

    if(root == NULL) return false;
    if(arePointsSame(root -> point, point)) return true;

    unsigned cd = depth % k;

    if (point[cd] < root -> point[cd])
        return searchRecursive(root -> left, point, depth + 1);

    return searchRecursive(root -> right, point, depth + 1);
}

// function to search for a point
bool search(node* root, int point[]){
    return searchRecursive(root, point, 0);
}

// helper function to print points inside region
void found(node *p){
    cout << "(";
    for(int i = 0; i < k; i++){
        cout << p->point[i];
        if(i+1 < k) cout << ", ";
    }
    cout << ")\n";
}

// checks if a specific point is inside region
bool inRegion(node *p, double RECDEF[]){
    for(int i = 0; i < k; i++){
        if(p->point[i] < RECDEF[2*i] || p->point[i] > RECDEF[2*i+1])
            return false;
    }
    return true;
}

// checks if bounds of the subtree intersect(partially lie inside) queried boundary
bool boundsIntersectRegion(double b[], double RECDEF[]){
    for(int i = 0; i < k; i++){
        if(b[2*i] > RECDEF[2*i+1] || b[2*i+1] < RECDEF[2*i])
            return false;
    }
    return true;
}

void copyBounds(double a[], double b[], int size){
    for(int i = 0; i < size; i++){
        b[i] = a[i];
    }    
}

// find all points inside given query region
void regionSearch(node *p, double b[], double RECDEF[], int depth){
    if(p == nullptr) return;

    if(inRegion(p, RECDEF))
        found(p);

    int cd = depth % k;
    double boundsLeft[2*k], boundsRight[2*k];
    copyBounds(b, boundsLeft, 2*k);
    copyBounds(b, boundsRight, 2*k);

    boundsLeft[2*cd + 1] = p -> point[cd];
    boundsRight[2*cd] = p -> point[cd];

    if(p->left && boundsIntersectRegion(boundsLeft, RECDEF))
        regionSearch(p->left, boundsLeft, RECDEF, depth + 1);

    if(p->right && boundsIntersectRegion(boundsRight, RECDEF))
        regionSearch(p->right, boundsRight, RECDEF, depth + 1);
}

//driver
int main(){

}

