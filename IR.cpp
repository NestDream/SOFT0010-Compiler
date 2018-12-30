#include<iostream>
#include<string>
#include"Node.h"
#include"func.h"
#include<list>
#include<map>
#include"innercode.h"
using namespace std;

int seq=0;
int tnum=1;
string label1="0";
string label2="0";
string label3="0";
int number=0;
int count=0;
int if_else=0;
bool if_over=false;
bool while_over=true;
bool for_true=false;
bool for_over=true;
Innercode innercode;
class IR{
    
public:
    
    string id;
    string op;
    string arg1;
    string arg2;
    string result;
    
    IR(string id,string op,string arg1,string arg2,string result)
    {
        this->id=id;
        this->op=op;
        this->arg1=arg1;
        this->arg2=arg2;
        this->result=result;
    }
    
};

list<IR> l;


// void Node::function_definition(Node* funcN)
// {
//     bool isdeclared = false;
//     funcNode declareFunc;
//     if(funcPool.find(funcName)!=funcPool.end())
//     {
//         if(funcPool[funcName].isdefinied)
//         {
//             cout<<"错误：函数重复定义"<<endl;
//         }
//         else
//         {
//             isdeclared = true;
//             //先删除掉函数池中的函数的声明
//             declareFunc = funcPool[funcName];
//             funcPool.erase(funcPool.find(funcName));
//         }
//     }
//     Block funBlock;
//     funBlock.isFunc = true;
//     funBlock.func.name = funcName;
//     funBlock.func.rtype = funcType;
// 	funBlock.func.isdefinied = true;
//     funcPool.insert({funcName, funBlock.func});
//     l.push_back(*(new IR("Function", funcName, ":", "","")));   

//     funcNode func = funcPool[funcName];
//     if(isdeclared)
//     {
//         if (func.rtype != declareFunc.rtype) {
// 			cout<<"错误：函数参数和返回类型不一致"<<endl;
//         }
// 		cout << funBlock.func.paralist.size() << endl;
// 		if (func.paralist.size() != declareFunc.paralist.size()) {
// 			cout<<"错误：函数参数个数不一致"<<endl;
// 		}
// 		for (int i = 0; i < funBlock.func.paralist.size(); i++) {
// 			if (func.paralist[i].type != declareFunc.paralist[i].type)
// 			cout<<"错误：函数定义时的参数和声明时不一致"<<endl;
// 		}
//     }

//     funBlock.func = func;


// }


// void Node::get_function_parameter(Node* node, string funcName,bool definite)
// {

// }

void dfs(Node* n){
    
    if(n->countOfChildren==0){return;}
    
    for (list<Node*>::iterator it=n->children.begin(); it != n->children.end(); it++)
    {
        
        Node* child=*it;
        
        if((child->name=="assignment_expression")&&(for_true==false)){
            string result=child->children.front()->detail;
            Node* factors=child->children.back();
            
            if(factors->countOfChildren==1){
                l.push_back(*(new IR(to_string(seq++),"=",factors->children.front()->detail,"NULL",result)));
            }
            else if(factors->countOfChildren==2){
                
                l.push_back(*(new IR(to_string(seq++),factors->detail,factors->children.front()->children.front()->detail,factors->children.back()->children.front()->detail,"t"+to_string(tnum))));
                l.push_back(*(new IR(to_string(seq++),"=","t"+to_string(tnum++),"NULL",result)));
            }
            if(number==3)
            {
                
                if(count==(if_else-1))
                {
                    l.push_back(*(new IR("GOTO",label3,"","","")));
                    l.push_back(*(new IR("Label",label2,"","","")));
                }
                count++;
            }

            
        }
        
        
        if(child->name=="while_stmt")
        {
            string arg1 = "";
            string arg2 = "";
            Node* temp;
            int count = 0;
            Node* while_exp = child->children.front();
            list<Node*>::iterator s;
            for (list<Node*>::iterator s=child->children.begin(); s!= child->children.end(); s++)
            {
                Node* c = *s;
                if(c->name=="simple_expression")
                {
                    //expression
                    Node* factor = c->children.front();
                    if(factor->countOfChildren==1)
                    {
                        arg1= factor->children.front()->detail;
                    }
                    list<Node*>::iterator ch;
                    for(ch= c->children.begin();ch!= c->children.end(); ch++ )
                    {
                        if(count==2)
                        {
                            break;
                        }
                        count++;
                        temp = *ch;
                    }
                    string op = temp->detail;
                    
                    Node* factor2 = c->children.back();
                    if(factor2->countOfChildren==1)
                    {
                        arg2= factor2->children.front()->detail;
                    }
                    
                    label1=innercode.getLabelName();
                    label2=innercode.getLabelName();
                    label3=innercode.getLabelName();
                    
                    l.push_back(*(new IR("Label",label1,"","","")));
                    l.push_back(*(new IR(to_string(seq++),op,arg1,arg2,"GOTO "+label2)));
                    l.push_back(*(new IR("GOTO",label3,"","","")));
                    l.push_back(*(new IR("Label",label2,"","","")));
                }
                
            }
        }
        

        if(child->name=="for_condition")
        {
            string arg1 = "";
            string arg2 = "";
            int co = 0;
            Node* temp;
            list<Node*>::iterator inner;
            for (list<Node*>::iterator inner=child->children.begin(); inner!= child->children.end(); inner++)
            {
                Node* cinner=*inner;
                if(cinner->name=="assignment_expression")
                {
                    for_true=true;
                    string result=cinner->children.front()->detail;
                    Node* factors2=cinner->children.back();
                    
                    if(factors2->countOfChildren==1){
                        l.push_back(*(new IR(to_string(seq++),"=",factors2->children.front()->detail,"NULL",result)));
                    }
                    else if(factors2->countOfChildren==2){
                        
                        l.push_back(*(new IR(to_string(seq++),factors2->detail,factors2->children.front()->children.front()->detail,factors2->children.back()->children.front()->detail,"t"+to_string(tnum))));
                        l.push_back(*(new IR(to_string(seq++),"=","t"+to_string(tnum++),"NULL",result)));
                    }
                
                }

                if(cinner->name=="simple_expression")
                {
                    //expression
                    Node* factor = cinner->children.front();
                    if(factor->countOfChildren==1)
                    {
                        arg1= factor->children.front()->detail;
                    }
                    list<Node*>::iterator ch;
                    for(ch= cinner->children.begin();ch!= cinner->children.end(); ch++ )
                    {
                        if(co==2)
                        {
                            break;
                        }
                        co++;
                        temp = *ch;
                    }
                    string op = temp->detail;
                    
                    Node* factor2 = cinner->children.back();
                    if(factor2->countOfChildren==1)
                    {
                        arg2= factor2->children.front()->detail;
                    }
                    
                    label1=innercode.getLabelName();
                    label2=innercode.getLabelName();
                    label3=innercode.getLabelName();
                    
                    l.push_back(*(new IR("Label",label1,"","","")));
                    l.push_back(*(new IR(to_string(seq++),op,arg1,arg2,"GOTO "+label2)));
                    l.push_back(*(new IR("GOTO",label3,"","","")));
                    l.push_back(*(new IR("Label",label2,"","","")));
                    
                }
            
            
            }
            
            
        }

        if(child->name=="for_body")
        {
            for_true=false;
            for_over=true;
        }
        

    

        if(child->name=="if_stmt")
        {
            string arg1 = "";
            string arg2 = "";
            Node* temp;
            Node* temp2;
            int count2 = 0;
            Node* son = child->children.front();
            list<Node*>::iterator next_statement;
            
            int son_num=0;
            for(next_statement= child->children.begin();next_statement!= child->children.end(); next_statement++ )
            {
                son_num++;
                temp2 = *next_statement;
            }
            
            list<Node*>::iterator s;
            
            
            if(child->countOfChildren==2) //没有else的情况
            {
                for (list<Node*>::iterator s=child->children.begin(); s!= child->children.end(); s++)
                {
                    Node* c=*s;
                    
                    if(c->name=="simple_expression")
                    {
                        Node* factor = c->children.front();
                        if(factor->countOfChildren==1)
                        {
                            arg1= factor->children.front()->detail;
                        }
                        
                        list<Node*>::iterator ch;
                        for(ch= c->children.begin();ch!= c->children.end(); ch++ )
                        {
                            if(count==2)
                            {
                                break;
                            }
                            count++;
                            temp = *ch;
                        }
                        
                        string op = temp->detail;
                        Node* factor2 = c->children.back();
                        if(factor2->countOfChildren==1)
                        {
                            arg2= factor2->children.front()->detail;
                        }
                        label1=innercode.getLabelName();
                        label2=innercode.getLabelName();
                        
                        l.push_back(*(new IR(to_string(seq++),op,arg1,arg2,"GOTO "+label1)));
                        l.push_back(*(new IR("GOTO",label2,"","","")));
                        l.push_back(*(new IR("Label",label1,"","","")));
                       
                    }
                    
                }
                
                
            }
            
            
            else //有else的情况
            { 
            
                for (list<Node*>::iterator s=child->children.begin(); s!= child->children.end(); s++)
                {
                    number++;
                    Node* c=*s;
                    
                    if(c->name=="simple_expression")
                    {
                        Node* factor = c->children.front();
                        if(factor->countOfChildren==1)
                        {
                            arg1= factor->children.front()->detail;
                        }
                        
                        list<Node*>::iterator ch;
                        for(ch= c->children.begin();ch!= c->children.end(); ch++ )
                        {
                            if(count2==2)
                            {
                                break;
                            }
                            count2++;
                            temp = *ch;
                        }
                        
                        string op = temp->detail;
                        Node* factor2 = c->children.back();
                        if(factor2->countOfChildren==1)
                        {
                            arg2= factor2->children.front()->detail;
                        }
                        label1=innercode.getLabelName();
                        label2=innercode.getLabelName();
                        label3=innercode.getLabelName();
                        l.push_back(*(new IR(to_string(seq++),op,arg1,arg2,"GOTO "+label1)));
                        l.push_back(*(new IR("GOTO",label2,"","","")));
                        //if(child->countOfChildren==2)
                        l.push_back(*(new IR("Label",label1,"","","")));
                        
                         
                    }
                    if(number == 2)
                    {
                       if_else = c->countOfChildren;
                    }
                
                    
                    
                }
                
           
            }
            
            
        
        }


        // if(child->name=="fun_declaration")
        // {
        //     Node* fu_temp;
        //     int son_num=0;
        //     list<Node*>::iterator next_statement;
        //     Node* last;
        //     Node* last2;
        //     Node* last3;
        //     string funcType = child->children.front()->name;
        //     for(next_statement= child->children.begin();next_statement!= child->children.end(); next_statement++ )
        //     {
        //         son_num++;
                
        //         if(son_num==2)
        //         {
        //             fu_temp = *next_statement;
        //             break;
        //         }
        //     }

        //     son_num=0;
        //     for(next_statement= child->children.begin();next_statement!= child->children.end(); next_statement++ )
        //     {
        //         son_num++;
        //         if(son_num==3)
        //         {
        //             last = *next_statement;
        //             break;
        //         }

        //     }

        //     string funcName = fu_temp->detail;
        //     list<Node*>::iterator next_next_statement;
        
        //     son_num=0;     
        //     last2 = last->children.front();
        //     last3 = last2->children.back();

        //     fun = last3->children.back();

           
        // }

        
        
        dfs(child);

        if(child->name=="if_stmt")
        {
            //label2 = innercode.getLabelName();
            if(child->countOfChildren==2)
            {
                l.push_back(*(new IR("Label",label2,"","","")));
                
            }
            else
            {
                
                l.push_back(*(new IR("Label",label3,"","","")));

            }
        }


        
        if(child->name=="while_stmt")
        {
            l.push_back(*(new IR("GOTO",label1,"","","")));
            l.push_back(*(new IR("Label",label3,"","","")));
        }

        if(child->name=="for_stmt")
        {
            l.push_back(*(new IR("GOTO",label1,"","","")));
            l.push_back(*(new IR("Label",label3,"","","")));
        }
        
        
        
    }
}

void IRCode(Node* uroot){
    cout<<"************************************"<<endl;
    cout<<"四元式"<<endl;
    cout<<"seq"<<'\t'<<"op"<<'\t'<<"arg1"<<'\t'<<"arg2"<<'\t'<<"result"<<endl;
    dfs(uroot);
    for (list<IR>::iterator it=l.begin(); it != l.end(); it++){
        cout<<it->id<<'\t'<<it->op<<'\t'<<it->arg1<<'\t'<<it->arg2<<'\t'<<it->result<<endl;
        
    }
}
