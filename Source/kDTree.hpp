#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct kDTreeNode
{
    vector<int> data;
    kDTreeNode* left;
    kDTreeNode* right;
    int dim;
    int label;
    bool chosen = false;
    kDTreeNode(vector<int> data, kDTreeNode* left = nullptr, kDTreeNode* right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    friend ostream &operator<<(ostream &os, const kDTreeNode &node)
    {
        os << "(";
        for (int i = 0; i < node.data.size(); i++)
        {
            os << node.data[i];
            if (i != node.data.size() - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
    
    kDTreeNode(const kDTreeNode* other) {
        this->data = other->data;
        this->left = (other->left) ? new kDTreeNode(other->left) : nullptr;
        this->right = (other->right) ? new kDTreeNode(other->right) : nullptr;
        this->dim = other->dim;
        this->label = other->label;
    }

    void setDim(const int& dimension) {
        this->dim = dimension;
    }

    void setLabel(const int& label) {
		this->label = label;
	}
};

class kDTree
{
private:
    int k;
    kDTreeNode *root;

public:
    kDTree(int k = 2);
    ~kDTree();
    void deleteTree(kDTreeNode* Node);

    kDTreeNode* getRoot();

    kDTreeNode* deepCopy(kDTreeNode* node);
    void clear(kDTreeNode* node);
    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other);

    string nodePrint(const vector<int>& point) const;

    void inorderTraversal() const;
    void inorderTraversalPrint(kDTreeNode* root, vector<kDTreeNode*> &vecPrint) const;
    void preorderTraversal() const;
    void preorderTraversalPrint(kDTreeNode* root, vector<kDTreeNode*> &vecPrint) const;
    void postorderTraversal() const;
    void postorderTraversalPrint(kDTreeNode* root, vector<kDTreeNode*> &vecPrint) const;

    int heightSup(kDTreeNode* root) const;
    int height() const;

    int nodeCountSup(kDTreeNode* root) const;
    int nodeCount() const;

    int leafCountSup(kDTreeNode* root) const;
    int leafCount() const;

    void insert(const vector<int>& point);

    kDTreeNode* insertSup(kDTreeNode* root, vector<int> point, unsigned depth);

    bool samePoints(vector<int> vec1, vector<int> vec2);
    kDTreeNode* searchSup(kDTreeNode* root, vector<int> point);
    bool search(const vector<int>& point);


    vector<vector<int>> merge(const vector<vector<int>>& left, vector<vector<int>>& right, const int& dim);
    vector<vector<int>> mergeSort(const vector<vector<int>>& p, const int& dim);
    void buildSup(const vector<vector<int>>& pointList, int dim);
    void buildTree(const vector<vector<int>>& pointList);

    kDTreeNode* removeFindReplaceNode(kDTreeNode* root, int dim);
    kDTreeNode* removeSup(kDTreeNode* root, const vector<int>& point);
    void remove(const vector<int>& point);

    double distance(vector<int> vec1, vector<int> vec2);
    void nearestNeighbour(const vector<int>& target, kDTreeNode* &best);
    void nearestNeighbourK(const vector<int>& target, kDTreeNode* &best);
    void nearestNeighbourSup(kDTreeNode* root, const vector<int>& target, kDTreeNode* &best, double &minDis);

    void setChosenTree(kDTreeNode* root);

    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList);

};

class kNN
{
private:
    int k;
    Dataset* X_train;
    Dataset* y_train;
    int numClasses;

    kDTree* tree;
public:
    kNN(int k = 5);
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
    int mostFrequent(vector<kDTreeNode*> arr, int n);
    vector<vector<int>> convertListListToVectorVector(const list<list<int>>& listOfLists);
};

// Please add more or modify as needed
