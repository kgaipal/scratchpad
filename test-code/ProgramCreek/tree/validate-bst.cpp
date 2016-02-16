//
// http://www.programcreek.com/2012/12/leetcode-validate-binary-search-tree-java/

#include <vector>
#include <assert.h>

bool validateBST(Node* root)
{
	bool compare = true;
	if (!root) {
		return compare;
	}

	// order left <= root < right

	if (root->left) {
		compare = compare && (root->left->data <= root->data);
	}

	if (root->right) {
		compare = compare && (root->data < root->right->data);
	}

	compare =&& (validateBST(root->left) && validateBST(root->right));

	return compare;
}

int main ()
{
	Node* root = createBST(std::vector<int>(2,3,4,5,6,7));

	assert(validateBST(root));

	return 0;
}
