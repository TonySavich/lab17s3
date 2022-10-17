#include <iostream>
#include <Windows.h>


struct tree {
    int znach;
    tree* l;
    tree* r;
    tree* p;
};





struct tree* addtr(struct tree* rt, std::string& s) {



    if (s[0] == '(' && s[1] != ',' && s.length() > 2) {
        s.erase(0, 1);
        rt->l = (struct tree*)malloc(sizeof(struct tree));
        rt->l->znach = (int)s[0] - 48;
        rt->l->l = rt->l->r = NULL;
        rt->l->p = rt;
        s.erase(0, 1);
        rt->l = addtr(rt->l, s);
    }



    if (s[0] == ',' && s.length() > 2) {

        s.erase(0, 1);
        if (rt->p != NULL) {
            rt->p->r = (struct tree*)malloc(sizeof(struct tree));
            rt->p->r->znach = (int)s[0] - 48;
            rt->p->r->l = rt->p->r->r = NULL;
            rt->p->r->p = rt->p;
            s.erase(0, 1);
            rt->p->r = addtr(rt->p->r, s);
        }
        else {
            rt->r = (struct tree*)malloc(sizeof(struct tree));
            rt->r->znach = (int)s[0] - 48;
            rt->r->l = rt->r->r = NULL;
            rt->r->p = rt;
            s.erase(0, 1);
            rt->r = addtr(rt->r, s);
        }

    }
    if ((s[0] == ')' || s[0] == '(' && s[1] == ',') && s.length() > 2) {
        s.erase(0, 1);
        if (rt->p != NULL) {
            rt->p = addtr(rt->p, s);
        }
        else {
            rt = addtr(rt, s);
        }
    }


    return rt;
}


void prim(tree* t)
{
    if (t == NULL) return;

    std::cout << t->znach << " "; 

    prim(t->l);
    prim(t->r); 
}




void centr(struct tree* root) {
    if (root != NULL) {
        if (root->l != NULL)
            centr(root->l);
        std::cout << root->znach << " ";
        if (root->r != NULL)
            centr(root->r);

    }

}

void konz(struct tree* root) {
    if (root != NULL) {
        if (root->l != NULL && root->znach>=0)
            konz(root->l);
        if (root->r != NULL && root->znach >= 0)
            konz(root->r);
        if(root->znach >= 0)
        std::cout << root->znach << " ";


    }

}




void Dob(tree* tree , int k) {
    if (tree->l == NULL) {
        tree->l = (struct tree*)malloc(sizeof(struct tree));
        tree->l->znach = k;
        tree->l->l = tree->l->r = tree->l->p = NULL;
        return void();
    }

    Dob(tree->l, k);
    return void();
    Dob(tree->r, k);
    return void();
    
}



int Poisk(tree* rt, int k) {
    int j = 1212;
    if (rt != NULL) {
        if (rt->znach == k) {
            j = k;
            return j;    
        }
        else {
            if (rt->l != NULL && j != k)
              j = Poisk(rt->l, k);
            if (rt->r != NULL && j !=k)
              j = Poisk(rt ->r, k);
        }

    }
    return j;
}



void freemem(tree* tree) {
    if (tree != NULL) {
        freemem(tree->l);
        freemem(tree->r);
        delete(tree);
    }
}



void SuperPoisk(tree* rt, int k) {

    if (rt != NULL) {
        if (rt->znach == k) {
            freemem(rt);
            return;
        }
        else {
            if (rt->l != NULL)
                SuperPoisk(rt->l, k);
            if (rt->r != NULL)
                 SuperPoisk(rt->r, k);
        }
    }
}

int main()
{
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN );
    setlocale(LC_ALL, "Russian");

    std::string tx;
    std::cout << "Введите дерево в формате линейно-скобочной записи" << std::endl;
    std::cin >> tx;
    struct tree* root;
    root = NULL;



    root = (struct tree*)malloc(sizeof(struct tree));
    root->znach = (int)tx[0] - 48;
    root->l = root->r = root->p = NULL;



    if (tx.length() > 1) {
        tx.erase(0, 1);

    }

    if (tx.length() > 1) {
        root = addtr(root, tx);
    }




    while (1) {
        std::cout << std::endl;
        std::cout << "Если вы хотите узнать, есть ли в дереве некоторое число, то нажмите 1" << std::endl;
        std::cout << "Если вы хотите удалить некоторую ветвь, то нажмите 2" << std::endl;
        std::cout << "Если вы хотите добавитб некоторое число, то нажмите 3" << std::endl;
        std::cout << "Если вы хотите завершить программу, то нажмите 4" << std::endl;
        int jo;
        std::cin >> jo;


        if (jo == 1) {
            std::cout << "Введите число" << std::endl;
            int rrr;
            std::cin >> rrr;
            int y = Poisk(root, rrr);
            if (y == 1212) {
                std::cout << "Такого числа нет" << std::endl;
            }
            else
            {
                std::cout << "Такое число есть" << std::endl;
            }
        }
        else if (jo ==2) {
            std::cout << "Введите число, с которого начинается ветвь" << std::endl;
            int giojo;
                std::cin >> giojo;
            SuperPoisk(root, giojo);
        }
        else if (jo==3) {
            std::cout << "Введите число" << std::endl;
            int uuuuuu;
                std::cin >> uuuuuu;
            Dob(root, uuuuuu);
        }
        else if (jo == 4) {
            konz(root);
            break;
        }


    }



}