#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

/*	����һ���㷨�ĺû����Դ��⼸���������֣�
	��1��ʱ�临�Ӷȣ��������еĳ�ʼ״̬�����������㷨�ı任��λ�Ȳ������
	���ս��״̬�����ѵ�ʱ�������
	��2���ռ临�Ӷȣ����ӳ�ʼ������״̬���ѵĿռ俪����
	��3�������㷨�ȶ��Եĸ���:�ȶ����㷨����������в���ı�Ԫ�ر˴�λ�õ�
	 ��Դ��򣬷�֮���ȶ��������㷨������ı��������
	��4��ʹ�ó�����������ˣ��ٺ��ʵ�ʱ��ʹ�ú��ʵ��㷨�����и��õĽ��
*/

/*
һ��ֱ�Ӳ�������: 
	�������(i>=1)����ʱ��ǰ���arr[0],arr[1]...arr[i-1]�Ѿ��ź����ˣ���ʱ
	arr[i]�Ӻ���ǰѰ���Լ��ò���ĵط���ԭ��������������
�ص��ܽ᣺
	1.Ԫ��Խ�ӽ�����ֱ�Ӳ��������㷨��ʱ��Ч�ʾ�Խ��
	2.ʱ�临�Ӷȣ�O(N^2)
	3.�ռ临�Ӷ�O(1)����һ���ȶ��������㷨
	4.�ȶ����ȶ�
*/
//ʵ��:��������
void InsertSort(vector<int>& arr){
	//�ѵ�һ��Ԫ�ؿ�������
	if (arr.size() <= 1){ return; }
	for (int i = 1; i < arr.size(); ++i){
		int tmp = arr[i];
		int end = i - 1;
		while (end>=0&&arr[end]>arr[i]){
			//ֻҪǰһ���Ⱥ�һ����ͺ���
			arr[end + 1] = arr[end]; 
			--end;
		}
		arr[end] = tmp;
	}
}

/*
����ϣ��������С��������
 ˼�룺ѡ��һ�����������Ѵ����������м�¼�ֳ�gap���飬���о���Ϊgap�ķ���ͬһ����
 ������ÿһ��ļ�¼�������� Ȼ����Сgap���ظ�����ķ���������������ﵽ=1
 ʱ�����м�¼��ͬһ�����ź���
 �ص��ܽ�:
	1.ϣ�������Ƕ�ֱ�Ӳ���������Ż�����������������Ϊֱ�Ӳ���������������
	��Խ�ߣ���Ч��Ҳ��Խ�ߣ�
	2.��gap>1ʱ����Ԥ����Ŀ�ľ�����������ӽ������򡣵�gap==1ʱ�������Ѿ�
	�ӽ������ˣ������ͻ�ܿ졣
	3.ʱ�临�Ӷ�O��N^1.3-N^2��
	4.�ȶ��ԣ����ȶ����޷���֤Ԫ�ر˴˼�����˳��
	5.Ȼ��ϣ��������������¶���ֱ�Ӳ���ã�������������ϣ����Ԥ�������������
	����ֱ�Ӳ������ĸɴ�
*/
//ʵ��ϣ������
void ShellSort(vector<int>& arr){
	if (arr.size() <= 1){ return; }
	int gap = arr.size();
	while (gap>1){
		gap = gap/2 ; //�趨�����С
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
����ѡ������
 ˼��:ÿһ�δӴ����������Ԫ����ѡ����С������һ��Ԫ�أ���������е���ʼλ�ã�
 ֱ��ȫ���������Ԫ������
 �ص��ܽ�:
	1.ʱ�临�Ӷ�:O(n^2)Ч�ʲ��ã�����ʹ��
	2.�ռ临�Ӷ�O��1��
	3.�ȶ��ԣ����ȶ�
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
�ġ�ð�����򷨣�
	˼��:��ֵ�ϴ�ļ�¼������β���ƶ�����С��������ǰ���ƶ�
�ص�:1.ð��������һ�ַǳ�������������
	 2.ʱ�临�Ӷȣ�O��N^2��
	 3.�ռ临�Ӷȣ�O��1��
	 4.�ȶ��ԣ��ȶ�
*/
void BubbleSort(vector<int>&arr){
	int size = arr.size();
	while (size){
	 int flag = 0;//�Ż�:���һ��������û�з����κν�������˵��������ֱ���˳�����
	  for (int j = 0; j < size-1; ++j){
		if (arr[j]>arr[j + 1]){ 
			swap(arr[j], arr[j + 1]);
			flag = 1;
		}
	  }
	  if (flag==0){ break; }
		--size; //ÿ�γ���һ�����ֵ��һ�ξͲ��ù���
    }
}

/*
�塢������
	˼�룺�����������ö��������ݽṹ����Ƶ�һ�������㷨������ѡ�������һ�֡�
	ͨ����������ѡ�����ݡ������򽨴�ѣ������С�ѣ�
�ص�:
	1.������ʹ�ö��������ݽṹЧ�ʸ���
	2.ʱ�临�Ӷ�:O��N*logN��
	3.�ռ临�Ӷ�: O(1)
	4.�ȶ��ԣ����ȶ�
*/
//����������Ҫ���е���  ����Ҫ����������ѵ����ʣ�����Ҫ�������µ����㷨��
void AdjustDown(vector<int>& arr,int root,int end){
	int parent = root;
	int child = root * 2 + 1; 
	while (child < end){
		if (child + 1 < end && arr[child + 1] > arr[child]){
			//���ж�����ǣ��ж���û���Һ��ӣ��еĻ�����������ӣ�����child++
			//ָ���Һ���
			++child;
		}
		if (arr[child] > arr[parent]){
			swap(arr[child], arr[parent]);
			//����
			parent = child;
			child = parent * 2 + 1;
		}
		else{
			break;
		}
	}
}

void HeapSort(vector<int>& arr){
	//���ø���������ѵ�����
	for (int i = (arr.size() - 2) / 2; i >= 0; --i){
		AdjustDown(arr, i,arr.size());
	}
	//��ʼ���ж�����
	int end = arr.size() - 1; //���һ��λ��
	while (end > 0){
		//ÿ�ΰ����/��С�������������
		swap(arr[0], arr[end]);
		//���е���
		AdjustDown(arr, 0,end);
		--end;
	}
}

/*
������������
 1.˼��:��ȡ������Ԫ�������е�ĳԪ����Ϊ��׼ֵ�����ո������뽫�����򼯺Ϸָ��
	�������У���������������Ԫ�ؾ�С�ڻ�׼ֵ����������������Ԫ�ؾ����ڻ�׼ֵ��
	Ȼ�������������ظ��ù��̣�ֱ������Ԫ�ض���������Ӧλ����λ�á�
 2.�����䰴�ջ�׼ֵ����Ϊ�������벿�ֵĳ�����ʽ�У�
	1.hoare�汾
	2.�ڿӷ�
	3.ǰ��ָ��汾
	4.ʱ�临�Ӷ�:O(N*logN)
	5.�ռ临�Ӷȣ�O(longN)
    6.�ȶ���:���ȶ�
3.���ڿ�������������������Ч�ʺܵͣ�������ѡ������ѡ������ΪKey����ֻ��һ�����䣩�ﵽO(N^2),
�������ǲ�ȡ����ȡ�з�����λ����λ����ΪKey�������任�����������������������
*/

//����ȡ��
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



//�Լ����ķ������߼��е㸴��,���ǰѱ�Ŀ��ֵС�ķ��󣬴�ķ��ң�����
//void Qsort(vector<int>& arr, int left,int right){
//	if (left>=right){ return; }
//	int begin = left, choose = right;
//	while (abs(begin-choose)>=1){
//		if (begin < choose){
//			//begin����
//			if (arr[choose] < arr[begin]){
//			   swap(arr[choose], arr[begin]);
//			   swap(begin, choose);
//			   ++choose;
//			}
//			else{--choose;}
//		}
//		else{
//			//choose����
//			if (arr[choose] > arr[begin]){
//				swap(arr[choose], arr[begin]);
//				swap(begin, choose);
//				--choose;
//			}
//			else{++choose;}
//		}
//	}
//	//ÿһ��������� ���з���
//	Qsort(arr, left, begin - 1); //���Ӳ���
//	Qsort(arr, begin + 1, right);//���Ӳ���
//}

//��׼д��������ָ�뷨�����͹̶�key��λ�ã�Ȼ��������ָ�������⣩
void HoareQsort(vector<int>& arr, int left, int right){
	if (left >= right){ return; }
	//����ȡ���Ż�
	int mid = GetIndex(arr,left,right);
	swap(arr[left], arr[mid]);

	int key = arr[left];//ÿ��ѡȡ�����һ��������Ϊkey�����һ��Ҳ�У�
	int max = left, min = right;
	while (max < min){
		//�ұߵ�min���ȴ��������ұ�keyС�����֣��ұ��ȿ�ʼ�ұ�֤�����һ������ָ�������ĵط���keyС������ֱ����key������
		while (max < min&&arr[min] >= key){ 
			--min; 
		}
		while (max < min&&arr[max] <= key){ 
			++max; 
		}
		//������ֵ
		swap(arr[max], arr[min]);
	}
		swap(arr[left], arr[min]); //����key�����ָ��������λ��
	//�ֶ���֮
		HoareQsort(arr, left, min - 1); //������
		HoareQsort(arr, min + 1, right);//������
}
//�ڿӷ� ���ַ����ǿ��Ը���Key��λ�ã�ÿ�α����ǵĵط��ĿӾ�û�ˣ�������ֵ�ĵط��γ��µĿ�
void PitQsort(vector<int>& arr, int left, int right){
	if (left >= right){ return; }
	//����ȡ���Ż�
	int mid = GetIndex(arr, left, right);
	swap(arr[left], arr[mid]);

	int key = arr[left];
	int begin = left, end = right, flag = 1;
	while (begin < end){
		//��Ϊ��
		while (begin < end && arr[end] >= key){ --end; } 
		arr[begin] = arr[end]; //���(ע�� �����Ժ�endλ������Ȼ��С��key��ֵ��������һ�β��������ѭ����ֱ������һѭ���������end�����)

		//��Ϊ��
		while (begin < end && arr[begin] <= key){ ++begin; }
		arr[end] = arr[begin]; //���

	}
	arr[begin] = key;//�������һ����
	//����
	PitQsort(arr, left, begin - 1);
	PitQsort(arr, begin + 1, right);
}

//ǰ��ָ�뷨 �÷����ǽ��������һ����Ϊkey��ǰָ����ȥ����С���ҵ�С��ָ��++��Ȼ��ǰ��ָ��ָ���ֵ����
void prSort(vector<int>& arr, int left, int right){
	if (left >= right){ return; }
	//����ȡ���Ż�
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
�ߡ��鲢����
   ˼�룺���η�����������������кϲ����õ���ȫ���������;����ʹÿ��������
   ������ʹ�����жμ������������������ϲ���һ���������Ϊ��·�鲢��
 �ص�:
	1.�鲢�����ȱ��������ҪO(N)�Ŀռ临�Ӷ�
	2.ʱ�临�Ӷ�O(N*logN)
	3.�ռ临�Ӷ�O(N)
	4.�ȶ��ԣ��ȶ�
*/

//ʵ��
vector<int> MergeSort(vector<int>&arr,int left,int right){
	vector<int> tmp;
	if (left == right){
		tmp.push_back(arr[left]);
		return tmp;
	}
	//������� �ֶ���֮
	int mid = ((right - left) >> 1) + left;
	vector<int> leftArr = MergeSort(arr,left, mid);
	vector<int> rightArr = MergeSort(arr, mid + 1, right);
	//�ϲ�
	auto itL = leftArr.begin();
	auto itR = rightArr.begin();
	//��һ��ռ����������鲢
	int size = leftArr.size() + rightArr.size(), i = 0;
	tmp.resize(size,0);//Ԥ���ٿռ䲢��ʼ��
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
���ϻ����϶��������򣬼����ڴ��е������ڴ�֧��������ʡ�
��������Ǹ�10��G���ļ�����������ô���أ�
�ļ��ڴ����У����̲�֧��������ʣ�֧�ִ��з��ʣ���Ը������ڴ����ϵ���������������Ҫʹ�õ�������

 1.�鲢�������þ��п�����������ص㣬һ�»��ֵ���λ1�Ŀռ����˳��������ٽ������ϼ��ɡ�
 2.����10G���ļ�������ȥ������̫�����ǿ��Խ����Ϊ10�ݣ�ÿһ��1G��1G�����������ԷŽ��ڴ�������㡣
 3.10��1G���ļ��Ž��ڴ�ʹ�ÿ��ų�Ϊ�������ó������й鲢���������ϼ���
 
*/
