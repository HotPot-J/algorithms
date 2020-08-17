#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

/*	评估一个算法的好坏可以从这几个方面入手：
	（1）时间复杂度：即从序列的初始状态到经过排序算法的变换移位等操作变道
	最终结果状态所花费的时间度量。
	（2）空间复杂度：即从初始到最终状态花费的空间开销。
	（3）排序算法稳定性的概念:稳定的算法在排序过程中不会改变元素彼此位置的
	 相对次序，反之不稳定的排序算法经常会改变这个次序
	（4）使用场景，因地制宜，再合适的时候使用合适的算法，会有更好的结果
*/

/*
一、直接插入排序: 
	当插入第(i>=1)个数时，前面的arr[0],arr[1]...arr[i-1]已经排好序了，此时
	arr[i]从后往前寻找自己该插入的地方，原来的数字往后移
特点总结：
	1.元素越接近有序，直接插入排序算法的时间效率就越高
	2.时间复杂度：O(N^2)
	3.空间复杂度O(1)，是一种稳定的排序算法
	4.稳定性稳定
*/
//实现:插入排序
void InsertSort(vector<int>& arr){
	//把第一个元素看作有序
	if (arr.size() <= 1){ return; }
	for (int i = 1; i < arr.size(); ++i){
		int tmp = arr[i];
		int end = i - 1;
		while (end>=0&&arr[end]>arr[i]){
			//只要前一个比后一个大就后移
			arr[end + 1] = arr[end]; 
			--end;
		}
		arr[end] = tmp;
	}
}

/*
二、希尔排序（缩小增量法）
 思想：选定一个人整数，把代排序中所有记录分成gap个组，所有距离为gap的分在同一组内
 ，并对每一组的记录进行排序 然后，缩小gap。重复上面的分组和排序工作，当达到=1
 时，所有记录在同一组内排好序。
 特点总结:
	1.希尔排序是对直接插入排序的优化（进行了与排序，因为直接插入排序数据有序
	度越高，其效率也就越高）
	2.当gap>1时都是预排序，目的就是让数组更接近于有序。当gap==1时，数组已经
	接近有序了，这样就会很快。
	3.时间复杂度O（N^1.3-N^2）
	4.稳定性：不稳定（无法保证元素彼此间的相对顺序）
	5.然而希尔不是所有情况下都比直接插入好，若数组有序，则希尔的预排序是无意义的
	不如直接插入来的干脆
*/
//实现希尔排序：
void ShellSort(vector<int>& arr){
	if (arr.size() <= 1){ return; }
	int gap = arr.size();
	while (gap>1){
		gap = gap/2 ; //设定分组大小
		for (int i = 0; i < arr.size()-gap; ++i){
			int tmp = arr[i + gap];
			int end = i;
			while (end >= 0 && arr[end]>tmp){
				arr[end + gap] = arr[end];
				end -= gap;
			}
			arr[end+gap] = tmp;
		}
	}
}

/*
三、选择排序：
 思想:每一次从待排序的数据元素中选出最小或最大的一个元素，存放在序列的起始位置，
 直到全部待排序的元素排完
 特点总结:
	1.时间复杂度:O(n^2)效率不好，很少使用
	2.空间复杂度O（1）
	3.稳定性：不稳定
*/

void SelectSort(vector<int>& arr){
	int size = arr.size();
	for (int i = 0; i < size; ++i){
		for (int j = i + 1; j < size; ++j){
			if (arr[j] < arr[i]){
				swap(arr[j], arr[i]);
			}
		}
	}
}

/*
四、冒泡排序法：
	思想:键值较大的记录向序列尾部移动，较小的向序列前部移动
特点:1.冒泡排序是一种非常容易理解的排序
	 2.时间复杂度：O（N^2）
	 3.空间复杂度：O（1）
	 4.稳定性：稳定
*/
void BubbleSort(vector<int>&arr){
	int size = arr.size();
	while (size){
	 int flag = 0;//优化:如果一趟排序中没有发生任何交换，则说明有序了直接退出排序
	  for (int j = 0; j < size-1; ++j){
		if (arr[j]>arr[j + 1]){ 
			swap(arr[j], arr[j + 1]);
			flag = 1;
		}
	  }
	  if (flag==0){ break; }
		--size; //每次沉底一个最大值下一次就不用管了
    }
}

/*
五、堆排序
	思想：堆排序是利用堆这种数据结构所设计的一种排序算法，他是选择排序的一种。
	通过堆来进行选择数据。（升序建大堆，降序件小堆）
特点:
	1.堆排序使用堆这种数据结构效率更高
	2.时间复杂度:O（N*logN）
	3.空间复杂度: O(1)
	4.稳定性：不稳定
*/
//堆排序首先要进行调堆  （需要让数组满足堆的性质，则需要进行向下调整算法）
void AdjustDown(vector<int>& arr,int root,int end){
	int parent = root;
	int child = root * 2 + 1; 
	while (child < end){
		if (child + 1 < end && arr[child + 1] > arr[child]){
			//该判断语句是，判断有没有右孩子，有的话如果大于左孩子，就让child++
			//指向右孩子
			++child;
		}
		if (arr[child] > arr[parent]){
			swap(arr[child], arr[parent]);
			//迭代
			parent = child;
			child = parent * 2 + 1;
		}
		else{
			break;
		}
	}
}

void HeapSort(vector<int>& arr){
	//先让该数组满足堆的性质
	for (int i = (arr.size() - 2) / 2; i >= 0; --i){
		AdjustDown(arr, i,arr.size());
	}
	//开始进行堆排序
	int end = arr.size() - 1; //最后一个位置
	while (end > 0){
		//每次把最大/最小的数调整到最后
		swap(arr[0], arr[end]);
		//进行调整
		AdjustDown(arr, 0,end);
		--end;
	}
}

/*
六、快速排序
 1.思想:任取待排序元素序列中的某元素作为基准值，按照该排序码将待排序集合分割成
	两子序列，左子序列中所有元素均小于基准值，右子序列中所有元素均大于基准值，
	然后左右最序列重复该过程，直到所有元素都排列在相应位置上位置。
 2.将区间按照基准值划分为左右两半部分的常见方式有：
	1.hoare版本
	2.挖坑法
	3.前后指针版本
	4.时间复杂度:O(N*logN)
	5.空间复杂度：O(longN)
    6.稳定性:不稳定
3.由于快速排序，在有序的情况加效率很低，（无论选最左还是选最右作为Key都是只有一个区间）达到O(N^2),
所以我们采取三数取中法将中位数的位置作为Key，并将其换到最左或者最右来进行排序
*/

//三数取中
int GetIndex(vector<int>& arr,int left,int right){
	int mid = (left + right) >> 1;
	if (arr[left] > arr[right]){
		if (arr[right] > arr[mid]){
			return right;
		}
		else{
			if (arr[left] > arr[mid]){
				return mid;
			}
			else{
				return left;
			}
		}
	}
	else{
		if (arr[left] > arr[mid]){
			return left;
		}
		else{
			if (arr[right] > arr[mid]){
				return mid;
			}
			else{
				return right;
			}
		}
	}
}



//自己理解的方法，逻辑有点复杂,我们把比目标值小的放左，大的放右（升序）
//void Qsort(vector<int>& arr, int left,int right){
//	if (left>=right){ return; }
//	int begin = left, choose = right;
//	while (abs(begin-choose)>=1){
//		if (begin < choose){
//			//begin在左
//			if (arr[choose] < arr[begin]){
//			   swap(arr[choose], arr[begin]);
//			   swap(begin, choose);
//			   ++choose;
//			}
//			else{--choose;}
//		}
//		else{
//			//choose在左
//			if (arr[choose] > arr[begin]){
//				swap(arr[choose], arr[begin]);
//				swap(begin, choose);
//				--choose;
//			}
//			else{++choose;}
//		}
//	}
//	//每一趟排序结束 进行分治
//	Qsort(arr, left, begin - 1); //左子部分
//	Qsort(arr, begin + 1, right);//右子部分
//}

//标准写法：左右指针法：（就固定key的位置，然后用左右指针解决问题）
void HoareQsort(vector<int>& arr, int left, int right){
	if (left >= right){ return; }
	//三数取中优化
	int mid = GetIndex(arr,left,right);
	swap(arr[left], arr[mid]);

	int key = arr[left];//每次选取区间第一个数字作为key（最后一个也行）
	int max = left, min = right;
	while (max < min){
		//右边的min开先从右往左找比key小的数字（右边先开始找保证了最后一次左右指针相遇的地方比key小，便于直接与key交换）
		while (max < min&&arr[min] >= key){ 
			--min; 
		}
		while (max < min&&arr[max] <= key){ 
			++max; 
		}
		//交换数值
		swap(arr[max], arr[min]);
	}
		swap(arr[left], arr[min]); //交换key和最后指针相遇的位置
	//分而治之
		HoareQsort(arr, left, min - 1); //左区间
		HoareQsort(arr, min + 1, right);//右区间
}
//挖坑法 该种方法是可以覆盖Key的位置，每次被覆盖的地方的坑就没了，拿走数值的地方形成新的坑
void PitQsort(vector<int>& arr, int left, int right){
	if (left >= right){ return; }
	//三数取中优化
	int mid = GetIndex(arr, left, right);
	swap(arr[left], arr[mid]);

	int key = arr[left];
	int begin = left, end = right, flag = 1;
	while (begin < end){
		//左为坑
		while (begin < end && arr[end] >= key){ --end; } 
		arr[begin] = arr[end]; //填坑(注意 填完以后end位置上依然是小于key的值，所以下一次不会走这个循环，直接走下一循环来填这个end这个坑)

		//右为坑
		while (begin < end && arr[begin] <= key){ ++begin; }
		arr[end] = arr[begin]; //填坑

	}
	arr[begin] = key;//填上最后一个坑
	//分治
	PitQsort(arr, left, begin - 1);
	PitQsort(arr, begin + 1, right);
}

//前后指针法 该方法是将区间最后一个作为key，前指针先去遍历小，找到小后指针++，然后前后指针指向的值交换
void prSort(vector<int>& arr, int left, int right){
	if (left >= right){ return; }
	//三数取中优化
	int mid = GetIndex(arr, left, right);
	swap(arr[left], arr[mid]);

	int prev = left - 1, rear = left;
	while (rear < right){
		if (arr[rear]<arr[right] && ++prev != rear){
			swap(arr[prev], arr[rear]);
		}
		++rear;
	}
	++prev;
	swap(arr[prev], arr[rear]);
	prSort(arr, left, prev - 1);
	prSort(arr, prev+1,right);
}

/*
七、归并排序
   思想：分治法，将已有序的子序列合并，得到完全有序的序列;即先使每个子序列
   有序，再使子序列段间有序。若将两个有序表合并成一个有序表，成为二路归并。
 特点:
	1.归并排序的缺点在于需要O(N)的空间复杂度
	2.时间复杂度O(N*logN)
	3.空间复杂度O(N)
	4.稳定性：稳定
*/

//实现
vector<int> MergeSort(vector<int>&arr,int left,int right){
	vector<int> tmp;
	if (left == right){
		tmp.push_back(arr[left]);
		return tmp;
	}
	//拆分区间 分而治之
	int mid = ((right - left) >> 1) + left;
	vector<int> leftArr = MergeSort(arr,left, mid);
	vector<int> rightArr = MergeSort(arr, mid + 1, right);
	//合并
	auto itL = leftArr.begin();
	auto itR = rightArr.begin();
	//开一块空间让这两个归并
	int size = leftArr.size() + rightArr.size(), i = 0;
	tmp.resize(size,0);//预开辟空间并初始化
	while (itL != leftArr.end()&&itR != rightArr.end()){
		if (*itL < *itR){
			tmp[i++] = *itL;
			++itL;
		}
		else{
			tmp[i++] = *itR;
			++itR;
		}
	}
	while (itL != leftArr.end()){
		tmp[i++] = *itL;
		++itL;
	}
	while (itR != rightArr.end()){
		tmp[i++] = *itR;
		++itR;
	}
	return tmp;
}


int main(){
	//vector<int> arr = {9,8,7,6,5,4,3,2,1,0};
	//InsertSort(arr);
	//ShellSort(arr);
	//SelectSort(arr);
	//BubbleSort(arr);
	//HeapSort(arr);
	vector<int> arr = { 49, 38, 65, 97, 76, 13, 27, 49 };
	//HoareQsort(arr, 0, arr.size() - 1);
	//PitQsort(arr, 0, arr.size() - 1);
	//PitQsort(arr, 0, arr.size() - 1);
	arr = MergeSort(arr, 0, arr.size() - 1);
	for (auto e : arr){
		cout << e << " ";
	}
	return 0;
}

/*
以上基本上都是内排序，即在内存中的排序，内存支持随机访问。
但是如果是给10个G的文件进行排序怎么排呢？
文件在磁盘中：磁盘不支持随机访问，支持串行访问，针对给这样在磁盘上的数据排序，我们需要使用到外排序。

 1.归并排序正好具有可以外排序的特点，一致划分到单位1的空间进行顺序的排序，再进行整合即可。
 2.但是10G的文件划分下去工作量太大，我们可以将其分为10份，每一份1G，1G的数据量可以放进内存进行运算。
 3.10个1G的文件放进内存使用快排成为有序，再拿出来进行归并排序再整合即可
 
*/
