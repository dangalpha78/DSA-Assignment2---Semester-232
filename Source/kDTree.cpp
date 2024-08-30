#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */


//kDTree class

//instructor
kDTree::kDTree(int k) {
    this->k = k;
    this->root = nullptr;
}

//destructor
kDTree::~kDTree() {
    deleteTree(this->root);

}

void kDTree::deleteTree(kDTreeNode* Node)
{
    if (Node == nullptr)
    {
        return;
    }
    deleteTree(Node->left);
    deleteTree(Node->right);
    delete Node;
}

kDTreeNode* kDTree::getRoot() {
    return this->root;
}  

kDTreeNode* kDTree::deepCopy(kDTreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    kDTreeNode* newNode = new kDTreeNode(node->data);
    newNode->left = deepCopy(node->left);
    newNode->right = deepCopy(node->right);
    newNode->dim = node->dim;
    newNode->label = node->label;
    return newNode;
}



void kDTree::clear(kDTreeNode* node) {
    if (node == nullptr) {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}

//op = for kDTree
const kDTree& kDTree::operator=(const kDTree& other) {
    if (this != &other) {
        clear(root); // Clear current contents of the tree
        root = deepCopy(other.root); // Deep copy the tree structure
    }
    return *this;
}

//copy constructor
kDTree::kDTree(const kDTree& other) {

    if (this != &other) {
        clear(root);
        this->root = deepCopy(other.root);
    }
}

string kDTree::nodePrint(const vector<int>& point) const {
    string result = "(";

    for (int i = 0; i < point.size(); i++) {
        result += to_string(point[i]);

        if (i == point.size() - 1) {
            result += ")";
            break;
        }

        result += ", ";
    }

    return result;
}

void kDTree::inorderTraversalPrint(kDTreeNode* root, vector<kDTreeNode*> &vecPrint) const {
    if (root != nullptr) {
        inorderTraversalPrint(root->left, vecPrint);
        vecPrint.push_back(root);
        inorderTraversalPrint(root->right, vecPrint);
    }
}

void kDTree::inorderTraversal() const {
    vector<kDTreeNode*> vecPrint;
    inorderTraversalPrint(this->root, vecPrint);
    for (int i = 0; i < vecPrint.size(); i++){
        cout << nodePrint(vecPrint[i]->data);
        if (i == vecPrint.size() - 1) break;
        cout << " ";
    }
}

void kDTree::preorderTraversalPrint(kDTreeNode* root, vector<kDTreeNode*> &vecPrint) const {
    if (root != nullptr) {
        vecPrint.push_back(root);
        preorderTraversalPrint(root->left, vecPrint);   
        preorderTraversalPrint(root->right, vecPrint);
    }
}

void kDTree::preorderTraversal() const {
    vector<kDTreeNode*> vecPrint;
    preorderTraversalPrint(this->root, vecPrint);
    for (int i = 0; i < vecPrint.size(); i++){
        cout << nodePrint(vecPrint[i]->data);
        if (i == vecPrint.size() - 1) break;
        cout << " ";
    }
}

void kDTree::postorderTraversalPrint(kDTreeNode* root, vector<kDTreeNode*> &vecPrint) const {
    if (root != nullptr) {
        postorderTraversalPrint(root->left, vecPrint);     
        postorderTraversalPrint(root->right, vecPrint);
        vecPrint.push_back(root);
    }
}

void kDTree::postorderTraversal() const {
    vector<kDTreeNode*> vecPrint;
    postorderTraversalPrint(this->root, vecPrint);
    for (int i = 0; i < vecPrint.size(); i++){
        cout << nodePrint(vecPrint[i]->data);
        if (i == vecPrint.size() - 1) break;
        cout << " ";
    }
}

int kDTree::heightSup(kDTreeNode* root) const {
    if (root == nullptr) return 0;
    return 1 + max(heightSup(root->left), heightSup(root->right));
}

int kDTree::height() const {
    if (!nodeCount()) return 0;
    return heightSup(this->root);
}

int kDTree::nodeCountSup(kDTreeNode* root) const {
    if (root == nullptr) return 0;
    return 1 + nodeCountSup(root->left) + nodeCountSup(root->right);
}

int kDTree::nodeCount() const {
    return nodeCountSup(this->root);
}

int kDTree::leafCountSup(kDTreeNode* root) const {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return leafCountSup(root->left) + leafCountSup(root->right);
}

int kDTree::leafCount() const {
    return leafCountSup(this->root);
}

kDTreeNode* kDTree::insertSup(kDTreeNode* root, vector<int> point, unsigned depth) {

    if (root == nullptr) {
        kDTreeNode* newNode = new kDTreeNode(point);
        newNode->setDim(depth % k);
        return newNode;
    }

    unsigned cd = depth % k;

    if (point[cd] < root->data[cd])
            root->left = insertSup(root->left, point, depth + 1);
    else
            root->right = insertSup(root->right, point, depth + 1);
        

    return root;
}

void kDTree::insert(const vector<int>& point) {
    this->root = insertSup(this->root, point, 0);
}


bool kDTree::samePoints(vector<int> vec1, vector<int> vec2) {
    for (int i = 0; i < k; i++) {
        if (vec1[i] != vec2[i]) return false;
    }
    return true;
}

kDTreeNode* kDTree::searchSup(kDTreeNode* root, vector<int> point) {
    if (root == nullptr) return nullptr;

    if (samePoints(root->data, point)) return root;
    
    if (point[root->dim] < root->data[root->dim]) return searchSup(root->left, point);

    return searchSup(root->right, point);
}

bool kDTree::search(const vector<int>& point){
    return searchSup(this->root, point);
}

string cc(vector<int> p) {
    string s = "(";
    for (int i = 0; i < p.size(); i++) {
        s += to_string(p[i]);
        if (i == p.size() - 1) {
            s += ")";
            break;
        }
        s += ",";
    }
    
    return s;
}

vector<vector<int>> kDTree::merge(const vector<vector<int>>& left, vector<vector<int>>& right, const int& dim) {
    vector<vector<int>> result;
    int i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i][dim] <= right[j][dim]) {
            result.push_back(left[i++]);
        }
        else {
            result.push_back(right[j++]);
        }
    }

    while (i < left.size()) {
        result.push_back(left[i++]);
    }

    while (j < right.size()) {
        result.push_back(right[j++]);
    }

    return result;
}

vector<vector<int>> kDTree::mergeSort(const vector<vector<int>>& p, const int& dim) {
    if (p.size() <= 1) {
        return p;
    }

    int mid = p.size() / 2;
    vector<vector<int>> left(p.begin(), p.begin() + mid);
    vector<vector<int>> right(p.begin() + mid, p.end());

    left = mergeSort(left, dim);
    right = mergeSort(right, dim);

    return merge(left, right, dim);
}

void kDTree::buildSup(const vector<vector<int>>& pointList, int dim) {
    if (pointList.empty()) return;

    if (pointList.size() == 1) {
        this->insert(pointList[0]);
        return;
    }

    int cd = (dim + 1) % k;
    vector<vector<int>> temp = mergeSort(pointList, dim);

    // for (auto i : temp){
    //     cout << cc(i) << " ";
    // }
    // cout << endl;
    int median = 0;
    // if (temp.size() % 2 == 1) median = temp.size() / 2;
    // else median = temp.size() / 2 - 1;
    median = (temp.size() - 1) / 2;

    while(median > 0 && temp[median][dim] == temp[median - 1][dim]){
        median--;
    }

    //cout << cc(temp[median]) << endl;

    this->insert(temp[median]);

    vector<vector<int>> left(temp.begin(), temp.begin() + median);
    vector<vector<int>> right(temp.begin() + median + 1, temp.end());

    buildSup(left, cd);
    buildSup(right, cd);
}


void kDTree::buildTree(const vector<vector<int>>& pointList) {
    this->deleteTree(this->root);
    this->root = nullptr;
    this->buildSup(pointList, 0);
    
}

kDTreeNode* kDTree::removeFindReplaceNode(kDTreeNode* root, int dim) {
    
    if (root == nullptr) return nullptr;
    
    if (root->dim == dim) {
        if (root->left == nullptr) return root;
        return removeFindReplaceNode(root->left, dim);
    }
    
    kDTreeNode* leftNode = removeFindReplaceNode(root->left, dim);
    kDTreeNode* rightNode = removeFindReplaceNode(root->right, dim);
    kDTreeNode* minNode = root;
    if (leftNode != nullptr && leftNode->data[dim] < minNode->data[dim]) {
        minNode = leftNode;
    }

    if (rightNode != nullptr && rightNode->data[dim] < minNode->data[dim]) {
        minNode = rightNode;
    }
    
    return minNode;
    
}

kDTreeNode* kDTree::removeSup(kDTreeNode* root, const vector<int>& point) {
    if (root == nullptr) return nullptr;

    if (samePoints(root->data, point)) {

        if (root->right) {
            kDTreeNode* replaceNode = removeFindReplaceNode(root->right, root->dim);
            //cout << "replace " << cc(replaceNode->data) << endl;
            root->data = replaceNode->data;
            //root->dim = replaceNode->dim;
            root->label = replaceNode->label;
            root->right = removeSup(root->right, replaceNode->data);
        }
        else if (root->left) {
            kDTreeNode* replaceNode = removeFindReplaceNode(root->left, root->dim);
            //cout << "replace " << cc(replaceNode->data) << endl;
            root->data = replaceNode->data;
            //root->dim = replaceNode->dim;
            root->label = replaceNode->label;
            root->right = root->left;
            root->left = nullptr;
            root->right = removeSup(root->right, replaceNode->data);
        }
        else {
            delete root;
            return nullptr;
        }

        return root;
        
    }

    if (point[root->dim] < root->data[root->dim])
        root->left = removeSup(root->left, point);
    else
        root->right = removeSup(root->right, point);
    return root;

}

void kDTree::remove(const vector<int>& point) {
    this->root = removeSup(this->root, point);

}

void kDTree::nearestNeighbour(const vector<int>& target, kDTreeNode* &best){
    double minDis = 999999999999;
    //kDTree* temp = this;
    this->setChosenTree(this->root);
    nearestNeighbourSup(this->root, target, best, minDis);
}

void kDTree::nearestNeighbourK(const vector<int>& target, kDTreeNode* &best){
    double minDis = 999999999999;
    this->nearestNeighbourSup(this->root, target, best, minDis);
}

// kDTreeNode* kDTree::nearestNeighbourSup(kDTreeNode* root, const vector<int>& target, kDTreeNode* &best){
    
//     if (root == nullptr) return best;

//     if ((best == nullptr || distance(root->data, target) <= distance(best->data, target)) && root->chosen == false) {
// 		best = root;
// 	}

// 	kDTreeNode* leftSide = nullptr;
// 	kDTreeNode* rightSide = nullptr;

//     if (target[root->dim] <= root->data[root->dim]) {
// 		leftSide  = root->left;
// 		rightSide = root->right;
// 	}
//     else {
// 		leftSide  = root->right;
// 		rightSide = root->left;
// 	}

// 	best = nearestNeighbourSup(leftSide, target, best);

//     if (rightSide != nullptr) {
//         if (distance(best->data, target) >= abs(target[root->dim] - root->data[root->dim])) {
// 			best = nearestNeighbourSup(rightSide, target, best);
// 		}
// 	}

//     return best;

// }

void kDTree::nearestNeighbourSup(kDTreeNode* root, const vector<int>& target, kDTreeNode* &best, double &minDis){
    
    if (root == nullptr) return;
    double disRoot = distance(root->data, target);
    

    if (!root->left && !root->right){
        if (root->chosen == false && disRoot < minDis){
            best = root;
            minDis = disRoot;
        }
        return;
    }


    if (target[root->dim] < root->data[root->dim]){
        nearestNeighbourSup(root->left, target, best, minDis);
        if (disRoot < minDis && root->chosen == false){
            best = root;
            minDis = disRoot;
        }
        if (minDis >= (double)abs(root->data[root->dim] - target[root->dim])){
            nearestNeighbourSup(root->right, target, best, minDis);
        }
    }
    else{
        nearestNeighbourSup(root->right, target, best, minDis);
        if (disRoot < minDis && root->chosen == false){
            best = root;
            minDis = disRoot;
        }
        if (minDis >= (double)abs(root->data[root->dim] - target[root->dim])){
            nearestNeighbourSup(root->left, target, best, minDis);
        }
    }
}

double kDTree::distance(vector<int> vec1, vector<int> vec2) {
    double dis = 0;

    for (int i = 0; i < vec1.size(); i++) {
        dis += pow(vec1[i] - vec2[i], 2);
    }
    return sqrt(dis);

}

void kDTree::setChosenTree(kDTreeNode* root){
    if (root == nullptr) return;
    root->chosen = false;
    setChosenTree(root->left);
    setChosenTree(root->right);
}

void kDTree::kNearestNeighbour(const vector<int>& target, int k, vector<kDTreeNode*>& bestList) {
    if (k > this->nodeCount()) k = this->nodeCount();

    this->setChosenTree(this->root);

    for (int i = 0; i < k; i++) {
        kDTreeNode* best = nullptr;
        nearestNeighbourK(target, best);
        best->chosen = true;
        kDTreeNode* temp = new kDTreeNode(best);
        bestList.push_back(temp);

        //tempTree.root = removeSup(tempTree.root, best->data);

    }

    this->setChosenTree(this->root);

    // for (auto i : bestList){
    //     cout << i->label << " ";
    // }

    // cout << endl;
    
}

kNN::kNN(int k){
    this->k = k;
    
}
void kNN::fit(Dataset& X_train, Dataset& y_train) {
    this->X_train = &X_train;
    this->y_train = &y_train;
    this->tree = new kDTree(X_train.data.front().size());

    vector<vector<int>> p_train = convertListListToVectorVector(this->X_train->data);
    vector<int> label;

    // for (auto i : X_train.data){
    //     vector<int> temp;
    //     for (auto j : i){
    //         temp.push_back(j);
    //     }
    //     p_train.push_back(temp);
    // }

    vector<vector<int>> copy = p_train;
    this->tree->buildTree(p_train); 

    for (auto i : this->y_train->data){
        label.push_back(i.front());
    }

    for (int i = 0; i < copy.size(); i++) {
        this->tree->searchSup(this->tree->getRoot(), copy[i])->setLabel(label[i]);

	}
    
}

vector<vector<int>> kNN::convertListListToVectorVector(const list<list<int>>& listOfLists) {
    vector<vector<int>> vectorOfVectors;
    // for (auto i : listOfLists) {
    //     vector<int> temp;
    //     for (auto j : i){
    //         temp.push_back(j);
    //     }
    //     vectorOfVectors.push_back(temp);
    // }

    for (const auto& innerList : listOfLists){
        vector<int> innerVec(innerList.begin(), innerList.end());
        vectorOfVectors.push_back(innerVec);
    }
    return vectorOfVectors;
}


Dataset kNN::predict(Dataset& X_test) {
    Dataset result;

    Dataset X_test1 = X_test;

    result.columnName.push_back("label");

    vector<vector<int>> p_test = convertListListToVectorVector(X_test1.data);

    if (X_train->data.size() == 0){
        result.data = X_test1.data;
        return result;
    }

    if (k > X_train->data.size()) k = X_train->data.size();

    for (int i = 0; i < p_test.size(); i++) {
        
        vector<kDTreeNode*> bestList;
        this->tree->kNearestNeighbour(p_test[i], this->k, bestList);
        int mostFrequentLabel = mostFrequent(bestList, this->k);
        list<int> temp;
        temp.push_back(mostFrequentLabel);

        result.data.push_back(temp);
	}   

    return result;
}

int kNN::mostFrequent(vector<kDTreeNode*> arr, int n) {
    int count[10] = { 0,0,0,0,0,0,0,0,0,0 };
    for (int i = 0; i < n; i++) {
        count[arr[i]->label]++;
    }

    int max = count[0];
    int index = 0;
    for (int i = 0; i < 10; i++) {
        if (count[i] > max) {
            max = count[i];
            index = i;
        }
    }

    return index;
}
double kNN::score(const Dataset& y_test, const Dataset& y_pred) {
    Dataset dataSet_test = y_test;
    Dataset dataSet_pred = y_pred;

    double size = dataSet_test.data.size();
    double accuracy = 0;

    vector<vector<int>> vecPred = convertListListToVectorVector(dataSet_pred.data);
    vector<vector<int>> vecTest = convertListListToVectorVector(dataSet_test.data);
    for (int i = 0; i < size; i++) {
        if (vecPred[i][0] == vecTest[i][0]) {
			accuracy++;
		}
	}

    return accuracy / size;
}
