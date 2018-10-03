#include "HashSet.h"




HashSet::HashSet(){
    fullCells=0;
    tableSize=11;
    a=31;
    b=149;
    elements=new int[tableSize];
    for(int i=0;i<tableSize;i++){
        elements[i]=-1;
    }
    flag=true;
}



HashSet & HashSet::operator=(const HashSet & ob){
  
    a=ob.a;
    b=ob.b;
    flag=ob.flag;
    fullCells=ob.fullCells;
    tableSize=ob.tableSize;
    if(elements!=NULL){
        delete [] elements;
    }
    elements=new int[tableSize];
    int i;
    for(i=0;i<tableSize;i++){
        elements[i]=ob.elements[i];
    }
    return *this;
}

bool HashSet::isAprime(int size){
    if(size==2){
        return true;
    }else{
        int i;
        for(i=3;i<=sqrt(size);i+=2){
            if(size%i==0){
                return false;
            }
        }
        return true;
    }
}

int HashSet::getAPrime(int prime){
    int other=0;
    int i,leftBound=2*prime-1,rightBound=4*prime+1;
    for( i=leftBound;i<=rightBound;i+=2){
        if(isAprime(i)){
            other=i;
            break;
        }
    }
    if(other==0){
        other=getAPrime(2*leftBound-1);
    }
    return other;
    
    
}



int HashSet::hash(int key,int divisor){
 
    return (_prime+a*key)%divisor;
    
}

void HashSet::reIn(int key){
    
    int k=hash(key,tableSize);
    if(elements[k]==-1){
        
        elements[k]=key; 
        
    } else{
       int plus=k;
        while(elements[k]!=-1){
            ++plus;
            k=hash(plus,tableSize);
        }
        elements[k]=key;
    }
      
}


void HashSet::reSize(int newsize){
    int i;
    delete [] elements;
    tableSize=newsize;
    elements =new int[tableSize];
    
    for(i=0;i<tableSize;i++){
        elements[i]=-1;
    } 

}

void HashSet::reallocation(){
    int i;
    int *temp=toArr();
    int newsize=getAPrime(tableSize);
    reSize(newsize);
    
    for(i=0;i<fullCells;i++){
           reIn(temp[i]);
    }
    delete [] temp;
}




void HashSet::insert(int key){
       if(!flag){
          elements=new int[tableSize];
          for(int i=0;i<tableSize;i++){
            elements[i]=-1;
          }flag=true;
       }
       
       
       int pos=hash(key,tableSize);
       int plus=pos;
       if(elements[pos]==key){
           return;
       }else if(elements[pos]==-1){
           elements[pos]=key;
       }else{
           
           while(elements[pos]!=-1){
               pos=hash(plus,tableSize);
               if(elements[pos]==key){
                   return;
               }
               ++plus;
               
           }
           elements[pos]=key;
       }
        ++fullCells;
       int limit=3*tableSize/7;
       if(fullCells>=limit){
           reallocation();
       } 
                 
       
}



int HashSet::search(int key){
    int pos=searchPos(key);
    if(pos==-1){
        return -1;
    }else{
        return elements[pos];
    }
}


int HashSet::searchPos(int key){
       int position=hash(key,tableSize);
       if(elements[position]==key){
            return position;
        }else{
          
            int iter=0;
            int plus=position;
            while(iter<tableSize){
                ++plus;
                position=hash(plus,tableSize);
                if(elements[position]==key){
                    return position;
                }
                iter++;
            }
            return -1;
        }  

}

void HashSet::remove(int key){
    int rm=searchPos(key);
    if(rm==-1){
        return;
    }else{
        elements[rm]=-1;
        fullCells--;
    }
   
    if(fullCells==0){
        for(int i=0;i<tableSize;i++){
            elements[i]=-1;
        }
        delete [] elements;
        flag=false;
    }
}

int* HashSet::toArr(){
    int* dt=new int[fullCells];
    
    int i,k=0;
    for(i=0;i<fullCells;i++){
        dt[i]=-1;
    }
   
    i=0;
    while(i<tableSize){
       
        if(elements[i]!=-1){
            dt[k++]=elements[i];
        }
        i++;
    }
    return dt;
}

void HashSet::sort(int *array,int left,int right){
    if (left < right) {
        int middle = left + (right - left) / 2;
        sort(array,left, middle);
        sort(array,middle + 1, right);
        merge(array,left, middle, right);
    }    
}

void HashSet::merge(int *arr, int left, int middle, int right) 
{
        int n1 = middle - left + 1;
        int n2 = right - middle;
 
        int *subL=new int[n1];
        int *subR=new int[n2];
        for (int i=0; i<n1; i++){ 
            subL[i] = arr[left + i];
        }
        for (int j=0; j<n2; j++){ 
              subR[j] = arr[middle + 1+ j];
        }
         
        int i = 0, j = 0;
        int k = left;
        while (i < n1 && j < n2){
            if (subL[i]<= subR[j]){
                arr[k] = subL[i];i++;
            }
            else{
                arr[k] = subR[j];j++;
            }k++;
        }
        
        while (i < n1){
            arr[k] = subL[i];k++;i++;
        }
        while (j < n2){
            arr[k] = subR[j];k++;j++;
        }
        delete [] subL;
        delete [] subR;
        
}
    
int* HashSet::giveSortedData(){
    int *array=toArr();
    sort(array,0,fullCells-1);
    return array;
}

void HashSet::printSort(std::ostream & my){
    if(fullCells>0){
        int* arr=giveSortedData();
        int i;
        for(i=0;i<fullCells;i++){
            my<<arr[i]<<" ";
        }
    }
}
