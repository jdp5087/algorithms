tree * construct_tree(const long arr[], const size_t arrlen, long (*getkey)(void*))
{
	int i = 0;
	long current;
	tree *T = init_tree();
	node *n;
	for (i; i < arrlen; i++) {
		current = arr[i];
		n = init_node(T, (void*)&current, getkey, RED);
		tree_insert(T, n);
	}
	return T;
}


int main()
{
	if
}
