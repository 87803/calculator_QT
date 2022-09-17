#include"calculator.h"
#include"sqstack.h"

double calculator::getResult(string& traverseResult)
{
    RPN = new LinkedQueue<string>;
    if (!RPN)
        exit(-1);
    dealNegativeNum();
    getReversePolishNotation();
    traverseResult = getTraverseResult();
    double ans=calculateResult();
    delete RPN;
    RPN = NULL;
    return ans;
}

string calculator::getTraverseResult()
{
    BTree bt;
    string result = "";
    createExpressionTree(bt);
    result += "先序遍历：";
    bt.recursivePreOrderTraverse(result);
    result += "\n中序遍历：";
    bt.recursiveInOrderTraverse(result);
    result += "\n后序遍历：";
    bt.recursivePostOrderTraverse(result);
    return result;
}

string calculator::isExpressionLegal()
{
    SqStack<char> parenthesisMatching;//判断符号匹配
    int i = 0;
    bool flag = true;
    while (i < infixExpression.length())
    {
        char c;
        if (infixExpression[i] == '(')
            parenthesisMatching.push('(');
        else if (infixExpression[i] == ')')
        {
            if (parenthesisMatching.stackEmpty())
            {
                flag = false;
                break;
            }
            else
                parenthesisMatching.pop(c);
        }
        i++;
    }
    if (!parenthesisMatching.stackEmpty())
        flag = false;
    if (!flag)
        return "括号不匹配";

    i = (int)infixExpression.length() - 1;
    while (infixExpression[i] == ')')
        i--;
    if ((infixExpression[i] >= '0' && infixExpression[i] <= '9')
        || infixExpression[i] == '.')
        return "无格式错误";
    return "缺少右操作数";
}

void calculator::setInfixExpression(string ie)
{
    infixExpression = ie;
}

void calculator::getReversePolishNotation()//中缀表达式转换为后缀表达式存入队列中
{
    SqStack<char> operatorStack;
    int i = 0;
    string num="";
    bool isNUM = false;//标注是否遇到数字
    while (infixExpression[i] != '\0')
    {
        if ((infixExpression[i] >= '0' && infixExpression[i] <= '9') || infixExpression[i] == '.')
        {
            num += infixExpression[i];
            isNUM = true;
        }
        else
        {
            if (isNUM)
            {
                RPN->enQueue(num);
                num = "";
                isNUM = false;
            }
            if (operatorStack.stackEmpty())
                operatorStack.push(infixExpression[i]);
            else if(infixExpression[i]=='(')
                operatorStack.push(infixExpression[i]);
            else if (infixExpression[i] == ')')
            {
                char temp=0;
                operatorStack.pop(temp);
                while (temp != '(')
                {
                    string temp2 = "";
                    temp2 += temp;
                    RPN->enQueue(temp2);
                    operatorStack.pop(temp);
                }
            }
            else if (infixExpression[i] == '*' || infixExpression[i] == '/')// 弹出所有优先级大于或者等于该运算符的栈顶元素，然后将该运算符入栈
            {
                char temp = 0;
                operatorStack.getTop(temp);
                while (!operatorStack.stackEmpty() && (temp == '*' || temp == '/'))//!operatorStack.stackEmpty() &&
                {
                    operatorStack.pop(temp);
                    string temp2 = "";
                    temp2 += temp;
                    RPN->enQueue(temp2);
                    operatorStack.getTop(temp);
                }
                operatorStack.push(infixExpression[i]);
            }
            else if (infixExpression[i] == '+' || infixExpression[i] == '-')// 让栈顶出栈直至栈空或遇到（,弹出所有优先级大于或者等于该运算符的栈顶元素，然后将该运算符入栈
            {
                char temp = 0;
                operatorStack.getTop(temp);
                while (!operatorStack.stackEmpty() && temp != '(')
                {
                    operatorStack.pop(temp);
                    string temp2 = "";
                    temp2 += temp;
                    RPN->enQueue(temp2);
                    operatorStack.getTop(temp);
                }
                operatorStack.push(infixExpression[i]);
            }
        }
        i++;
    }
    if (isNUM)//
    {
        RPN->enQueue(num);
        num = "";
    }
    while (!operatorStack.stackEmpty())
    {
        char temp;
        operatorStack.pop(temp);
        string temp2 = "";
        temp2 += temp;
        RPN->enQueue(temp2);
    }
}

void calculator::dealNegativeNum()//处理中缀表达式中的负数，便于后续转换
{
    int i = 0, j = (int)infixExpression.length();
    if (infixExpression[0] == '-')			//第一位数字为负数时
    {
        infixExpression += "     ";
        while (j > 0)
            infixExpression[j + 5] = infixExpression[--j];
        infixExpression[j++] = '(';
        infixExpression[j++] = '0';
        infixExpression[j++] = '-';
        infixExpression[j++] = '1';
        infixExpression[j++] = ')';
        infixExpression[j] = '*';
    }
    while (infixExpression[i] != '\0')//非第一位负数时
    {
        if (infixExpression[i] == '(' && infixExpression[i + 1] == '-')
        {
            j = (int)infixExpression.length();
            infixExpression += "     ";
            while (j > i + 1)
                infixExpression[j + 5] = infixExpression[--j];
            infixExpression[j++] = '(';
            infixExpression[j++] = '0';
            infixExpression[j++] = '-';
            infixExpression[j++] = '1';
            infixExpression[j++] = ')';
            infixExpression[j] = '*';
            i += 5;
        }
        i++;
    }
}

void calculator::createExpressionTree(BTree& bt)
{
   LinkedQueue<string> templq;
   string temp;
   SqStack<BtNode*> tempsq;
   while (!RPN->queueEmpty())
   {
       RPN->deQueue(temp);
       templq.enQueue(temp);
       BtNode* bn=new BtNode;
       bn->data = temp;
       bn->lChild = NULL;
       bn->rChild = NULL;
       if (temp[0] != '+' && temp[0] != '-' && temp[0] != '*' && temp[0] != '/')//如果是数字，结点入栈
           tempsq.push(bn);
       else//如果是运算符，则弹出两个数字结点，第一个作为右子树，第二个作为左子树，然后入栈
       {
           BtNode* bn2=NULL;
           tempsq.pop(bn2);
           bn->rChild = bn2;
           tempsq.pop(bn2);
           bn->lChild = bn2;
           tempsq.push(bn);
       }
   }
   while (!templq.queueEmpty())//还原原始队列
   {
       templq.deQueue(temp);
       RPN->enQueue(temp);
   }
   BtNode* bn2=NULL;
   tempsq.pop(bn2);
   bt.tree = bn2;
}

double calculator::calculateResult()
{
    SqStack<double> numStack;
    double leftNum=0;
    double rightNum=0;
    string temp;
    try {
        while (!RPN->queueEmpty())
        {
            RPN->deQueue(temp);
            if (temp[0] == '+' || temp[0] == '-' || temp[0] == '*' || temp[0] == '/')
            {
                numStack.pop(rightNum);
                numStack.pop(leftNum);
                switch (temp[0])
                {
                case '+':
                    numStack.push(leftNum + rightNum);
                    break;
                case '-':
                    numStack.push(leftNum - rightNum);
                    break;
                case '*':
                    numStack.push(leftNum * rightNum);
                    break;
                case '/':
                    numStack.push(leftNum / rightNum);
                    break;
                }
            }
            else
            {
                bool isPoint = false;//标记是否存在小数点
                double point = 1;
                double num = 0;
                for (int i = 0, len = (int)temp.length(); i < len; i++)
                {
                    if (temp[i] != '.' && !isPoint)
                        num = num * 10 + temp[i] - '0';
                    else if (temp[i] != '.' && isPoint)
                    {
                        point *= 0.1;
                        num += (temp[i] - '0') * point;//- '0'
                    }
                    else
                        isPoint = true;
                }
                numStack.push(num);
            }
        }
        double ans=0;
        numStack.pop(ans);
        return ans;//cout << "\n结果是" << ans << endl;

    }
    catch(exception e) {
        return -1;
        cout << "错误！";
    }

}
