// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Create a retained reference tree with three writable leaf references.
struct TreeNode;
struct TreeRef;
struct TreeResult;
struct TreeLink;
extern "C" {
    TreeNode *func_002BA6B8();
    TreeRef *func_0012B6C8(TreeRef *,TreeNode *);
    void func_0012BC20(TreeRef *);
    void func_0012BDD8(TreeRef *,int);
    void func_002BA760(TreeResult *,TreeNode *);
    void func_002BA780(TreeLink *,TreeNode *);
    void func_002BA840(TreeNode *,int);
}
struct TreeRef {
    short tag;
    short references;
    union {
        int number;
        float real;
        void *pointer;
    }
    value;
    TreeRef &operator=(TreeNode *node) {
        return *func_0012B6C8(this,node);
    }
    void SetTag(int tag) {
        func_0012BC20(this);
        func_0012BDD8(this,tag);
    }
};
struct TreeLink {
    TreeNode *p;
    void operator=(TreeNode *node) {
        func_002BA780(this,node);
    }
};
struct TreeNode : TreeRef {
    unsigned int trackedLinks;
    TreeLink next;
    void SetNext(TreeNode *node) {
        next=node;
    }
};
struct TreeResult {
    TreeNode *p;
    TreeResult() {
    }
    TreeResult(const TreeResult &);
    TreeResult(TreeNode *node) {
        func_002BA760(this,node);
    }
    void Set(TreeNode *node) {
        func_002BA760(this,node);
    }
    TreeNode *operator->() {
        return p;
    }
    ~TreeResult() {
        TreeNode *node=p;
        if (node && --node->references==0) func_002BA840(node,3);
    }
};
typedef char CheckTreeRef8[(sizeof(TreeRef)==8)?1:-1];
typedef char CheckTreeNode16[(sizeof(TreeNode)==16)?1:-1];
typedef char CheckTreeResult4[(sizeof(TreeResult)==4)?1:-1];
extern "C" TreeResult func_001236B0(TreeRef **firstOutput,TreeRef **secondOutput,TreeRef **thirdOutput) {
    TreeResult tree;
    tree.Set(func_002BA6B8());
    tree->TreeRef::operator=(func_002BA6B8());
    TreeNode *root=(TreeNode *)tree->value.pointer;
    TreeRef *firstBranch=root;
    *firstBranch=func_002BA6B8();
    root->SetNext(func_002BA6B8());
    TreeNode *nextBranch=root->next.p;
    nextBranch->SetNext(func_002BA6B8());
    TreeNode *firstLeaf=(TreeNode *)firstBranch->value.pointer;
    firstLeaf->SetTag(0x10);
    firstLeaf->SetNext(func_002BA6B8());
    *firstOutput=firstLeaf->next.p;
    TreeNode *secondBranch=root->next.p;
    secondBranch->TreeRef::operator=(func_002BA6B8());
    TreeNode *secondLeaf=(TreeNode *)secondBranch->value.pointer;
    secondLeaf->SetTag(0x10);
    secondLeaf->SetNext(func_002BA6B8());
    *secondOutput=secondLeaf->next.p;
    TreeNode *thirdBranch=secondBranch->next.p;
    thirdBranch->TreeRef::operator=(func_002BA6B8());
    TreeNode *thirdLeaf=(TreeNode *)thirdBranch->value.pointer;
    thirdLeaf->SetTag(0x10);
    thirdLeaf->SetNext(func_002BA6B8());
    *thirdOutput=thirdLeaf->next.p;
    return TreeResult(tree.p);
}
