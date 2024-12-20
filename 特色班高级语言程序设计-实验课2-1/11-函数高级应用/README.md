## 函数递归

函数 A 在其函数体中直接包含对它自己的调用语句，这种调用称为 **直接递归调用**，函数 A 称为（直接）递归函数

函数 A 在其函数体中间接地包含对它自己的调用，例如 A 调用函数 B， 但函数 B 又调用函数 A，则函数 A称为 **间接递归函数**

```cpp
float fac (int n) {
	if (n < 2) return 1;
	return fac (n - 1) * n;
}
```

递归函数的实际计算过程与递归次序相反，例如，设 `n=4`，计算 `fac(4)` 的 递归次序是： `fac(4) → fac(3) → fac(2) → fac(1)`，而实际计算过程则正好相反：`fac(1)=1，fac(2)=fac(1) * 2=2，fac(3)=fac(2) * 3=6， fac(4)=fac(3) * 4=24`

## 函数递归的终止条件

在递归函数体中，无论如何，应该存在使得递归趋向于终止的语句

