#include "bptree.h"
#include <vector>
#include <sys/time.h>

struct timeval
cur_time(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t;
}

void
print_tree_core(NODE *n)
{
	printf("["); 
	for (int i = 0; i < n->nkey; i++) {
		if (!n->isLeaf) print_tree_core(n->chi[i]); 
		printf("%d", n->key[i]); 
		if (i != n->nkey-1 && n->isLeaf) putchar(' ');
	}
	if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
	printf("]");
}

void
print_tree(NODE *node)
{
	print_tree_core(node);
	printf("\n"); fflush(stdout);
}

NODE *
find_leaf(NODE *node, int key)
{
	int kid;

	if (node->isLeaf) return node;
	for (kid = 0; kid < node->nkey; kid++) {
		if (key < node->key[kid]) break;
	}

	return find_leaf(node->chi[kid], key);
}

NODE *
insert_in_leaf(NODE *leaf, int key, DATA *data)
{

	int i;
	for(i = 0; i < leaf->nkey; i++)
	{
		if(leaf->key[i] == key)
		{
			leaf->chi[i] = (NODE *)data;
			return leaf;
		}
	}

	if (key < leaf->key[0]) { 
		for (i = leaf->nkey; i > 0; i--) {
			leaf->chi[i] = leaf->chi[i-1];
			leaf->key[i] = leaf->key[i-1];
		} 
		leaf->key[0] = key;
		leaf->chi[0] = (NODE *)data;
	}

	else {
		for (i = 0; i < leaf->nkey; i++) {
			if (key < leaf->key[i]) break;
		}
		for (int j = leaf->nkey; j > i; j--) {		
			leaf->chi[j] = leaf->chi[j-1] ;
			leaf->key[j] = leaf->key[j-1] ;
		} 
		leaf->key[i] = key;
		leaf->chi[i] = (NODE *)data;
	}

	leaf->nkey++;

	return leaf;
}

NODE *
alloc_leaf(NODE *parent)
{
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = true;
	node->parent = parent;
	node->nkey = 0;

	return node;
}

void insert_into_parent(NODE *leaf, NODE *new_leaf, int new_key)
{
	if(leaf->parent == NULL)
	{
		NODE *new_root = alloc_leaf(NULL);
		new_root->isLeaf = false;
		new_root-> key[0] = new_key;
		new_root->chi[0] = leaf;
		new_root->chi[1] = new_leaf;
		new_root->nkey = 1;
		leaf->parent = new_root;
		new_leaf->parent = new_root;
		Root = new_root;
		return; 
	}
	else{
		NODE *parent = leaf->parent;

		if(parent->nkey < (N))
		{
			int insert_position;
			for(insert_position = 0; insert_position < parent->nkey; insert_position++)
			{
				if(new_key < parent->key[insert_position])
					break;
			}
			for(int i = parent->nkey; i > insert_position; i--)
			{
				parent->key[i] = parent->key[i - 1];
				parent->chi[i + 1] = parent->chi[i];
			}

			parent->key[insert_position] = new_key;
			parent->chi[insert_position + 1] = new_leaf;
			parent->nkey++;
			new_leaf->parent = parent;
		}
		else
		{
			NODE *new_parent = alloc_leaf(parent->parent);
			new_parent->isLeaf = false;

			TEMP temp;
			for(int i = 0; i < N; i++)
			{
				temp.key[i] = parent->key[i];
				temp.chi[i] = parent->chi[i];
			}
			temp.chi[N-1] = parent->chi[N-1];

			int insert_position;
			for(insert_position = 0; insert_position < N; insert_position++)
			{
				if(new_key < temp.key[insert_position])
				{
					break;
				}
			}
			for(int i = N; i > insert_position; i--)
			{
				temp.key[i] = temp.key[i - 1];
				temp.chi[i + 1] = temp.chi[i];
			}
			temp.key[insert_position] = new_key;
			temp.chi[insert_position + 1] = new_leaf;
			temp.nkey = N;

			parent->nkey = N / 2;
			new_parent->nkey = (N) - parent->nkey;

			for(int i = 0; i < parent->nkey; i++)
			{
				parent->key[i] = temp.key[i];
				parent->chi[i] = temp.chi[i];
			}
			parent->chi[parent->nkey] = temp.chi[parent->nkey];

			for(int i = 0; i < new_parent->nkey; i++)
			{
				new_parent->key[i] = temp.key[i + parent->nkey + 1];
				new_parent->chi[i] = temp.chi[i + parent->nkey + 1];
			}
			new_parent->chi[new_parent->nkey] = temp.chi[temp.nkey];

			insert_into_parent(parent, new_parent, new_parent->key[0]);
		}
	}

}

void 
insert(int key, DATA *data)
{
	NODE *leaf;

	if (Root == NULL) {
		leaf = alloc_leaf(NULL);
		Root = leaf;
	}
  	else 
	{
    	leaf = find_leaf(Root, key);
  	}

	if (leaf->nkey < (N-1)) {
		insert_in_leaf(leaf, key, data);
	}

	else 
	{ // split

        NODE *new_leaf;
		new_leaf = alloc_leaf(leaf->parent);

		int temp_keys[N];
		DATA *temp_data[N];

		for(int i = 0; i < N; i++)
		{
			temp_keys[i] = leaf->key[i];
			temp_data[i] = (DATA *)leaf->chi[i];
		}
		temp_keys[N-1] = key;
		temp_data[N-1] = data;

		std::cout << "temp_keys before sorting: ";

		for(int i = 0; i < N; i++)
		{
			std::cout << temp_keys[i] << " ";
		}
		std::cout << std::endl;

		for(int i = 0; i < N; i++)
		{
			for(int j = i + 1; j < N; j++)
			{
				if(temp_keys[i] > temp_keys[j])
				{
					int temp = temp_keys[i];
					temp_keys[i] = temp_keys[j];
					temp_keys[j] = temp;

					DATA *tempD = temp_data[i];
					temp_data[i] = temp_data[j];
					temp_data[j] = tempD;
				}
			}
		}

		std::cout << "temp_keys after sorting: ";

		for(int i = 0; i < N; i++)
		{
			std::cout << temp_keys[i] << " ";
		}
		std::cout << std::endl;

		int split_index = N / 2;
		leaf->nkey = split_index;
		new_leaf->nkey = N - split_index;

		for (int i = 0; i < split_index; i++) {
    		leaf->key[i] = temp_keys[i];
    		leaf->chi[i] = (NODE *)temp_data[i];
		}

		for (int i = 0; i < new_leaf->nkey; i++) {
    		new_leaf->key[i] = temp_keys[i + split_index];
    		new_leaf->chi[i] = (NODE *)temp_data[i + split_index];
		}


		insert_into_parent(leaf, new_leaf, new_leaf->key[0]);
	}
}

void
init_root(void)
{
	Root = NULL;
}

int 
interactive()
{
  int key;

  std::cout << "Key: ";
  std::cin >> key;

  return key;
}

int
main(int argc, char *argv[])
{
  struct timeval begin, end;

	init_root();

	printf("-----Insert-----\n");
	begin = cur_time();
  while (true) {
		insert(interactive(), NULL);
    print_tree(Root);
  }
	end = cur_time();

	return 0;
}
