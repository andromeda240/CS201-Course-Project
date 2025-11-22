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
Region query
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

//driver
int main(){

}

