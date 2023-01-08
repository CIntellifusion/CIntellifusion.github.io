# Design NN in C++ referring to torch

## Dataset and Data loader

class dataset is the abstract class for all the dataset. We should always use it to load our data, even if we don’t use torch.

Dataset has two key attribute that need to be rewrite by users.

```python
def __len__()
def __getitem__()
```

this two function are easy to understand. Considering all the dataset you may have to use, which are not always supposed to be iterable. So once you have the length of the dataset and know how to get an item from it, you can get a mini batch and decide to shuffle it or not. 

**Remember that the tensor should be adapted to FloatTensor for data, to LongTensor for label**

<font color='red'> otherwise it will rise fault with data type</font>

For example, suppose we have a DataFrame, which is very common if we get data from kaggle.  We may build our Dataset like this

```python
class MyLoder(DataLoader):
    def __init__(self,data,label):
        self.data = np.array(data).astype(float)
        self.label = np.array(label)
        self.data = torch.from_numpy(self.data).type(torch.FloatTensor)
        self.label = torch.from_numpy(self.label).type(torch.LongTensor)
    def __getitem__(self, idx):
        return self.data[idx],self.label[idx]
    def __len__(self):
        return len(self.data)
```



cause the original type are iterable, we just need to few codes to realize it.

but when we have a number of photos to recongize, it can be a little bit harder.



> Now We look further into Dataset

## Handle a batch of files

Given that we are going to do a audio recongnize programs. And take MEAD dataset for an example.

In this case, we need the help of os package which provides a number of powerful functions to handle directories and files. 

The organization of MEAD dataset is like:

```
MEAD-
	-M001
		-audio
			-angry
				-oo1.m4a
				-002.m4a
				-003.m4a
				....
			-happy
			...
		-video
	-M002
	-M003
	...
```

so our sample is a single .m4a file

and we have to handle directory to fetch a file.

```python
class FetchM4a(nn.module):
    def __init__(self,filepath):
        #omit a relatively complex steps of handlings path
    def __getitem__():
        	1. get a random number
            	2. read the file through os 
    def __len__():
        	len(os.listdir(path)).
```

