
#include "arifm_mirea.h"
#include <string.h>

const unsigned int min(unsigned int a, unsigned int b) { return a > b ? b : a; }
const unsigned int max(unsigned int a, unsigned int b) { return a > b ? a : b; }

void umn(int n, unsigned int *a, unsigned int *b, unsigned int *c)
{
	unsigned long long a1[MAXLEN];
	unsigned long long b1[MAXLEN];
	unsigned long long d;
	int i,j;

	i = n;
	while(--i>=0){ a1[i] = a[i]; b1[i] = b[i];}

	i = 2*n;
	while (--i >= 0) c[i] = 0;

	for(i = 0; i < n; i++)
	{
		d = 0;
		for(j = 0; j < n; j++)
		{
			d += (unsigned long long) a1[j] * b1[i] + c[i+j];
			c[i+j] = d;
			d >>= BIT_INT;
		}
		c[i+j] = d;
	}
}

int first_bit(int n, unsigned int *a)
{
	int i,j;
	for (i = n-1; i>=0; i--)
	{
		if(a[i])
		{
			for (j = (BIT_INT - 1); j>=0; j--)
			{
				if(a[i] >> j)
					return i * BIT_INT + j;
			}
		}
	}
	return -1;
}

int cmp(int n, unsigned int *a, unsigned int *b)
{
	int i = n-1;
	while(i >= 0 && a[i] == b[i]) 
		i--;
	if(i < 0) 
		return 0;
	if(a[i] > b[i]) 
		return 1;
	return -1;
}

void sum(int n, unsigned int *a, unsigned int *b, unsigned int *c)
{
	unsigned int d = 0;
	unsigned long long s;
	for(int i = 0; i < n; i++)
	{
		s = (unsigned long long) a[i] + b[i] + d;
		c[i] = s;
		d = s >> BIT_INT;
	}
}

void raz(int len, unsigned int * a, unsigned int * b, unsigned int * c)
{
	int i;
	unsigned int d;
	unsigned int h=0;
	for(i=0;i<len;i++)
	{
		d=(unsigned int)a[i] - b[i] - h;
		c[i] = d;
		h = d >> (BIT_INT-1);
	}
}

void sum_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c)
{
	sum(len,a,b,c);
	while(cmp(len,c,p)>=0)
		raz(len,c,p,c);
}

void raz_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c)
{
	if(cmp(len,a,b)!=-1)
		raz(len,a,b,c);
	else
	{
		raz(len,a,b,c);
		sum(len,c,p,c);
	}
	while(cmp(len,c,p)>=0)
		raz(len,c,p,c);
}
// a �� ������ p
void mod_p(unsigned int * a, int n1, unsigned int * p, int n2)
{
	int m1=first_bit(n1,a);
	int m2=first_bit(n2,p);
	if(m2>m1)
		return;
	else if(m1==m2)
	{
		if(cmp(min(n1,n2),a,p)==-1)
			return;
	}
	int len=max(n1,n2);
	unsigned int * c = new unsigned int[len];
	unsigned int * p1 = new unsigned int[len];
	memset(p1,0,len*sizeof(int));
	memcpy(p1,p,n2*sizeof(int));
	unsigned int * a1 = new unsigned int[len];
	memset(a1,0,len*sizeof(int));
	memcpy(a1,a,n1*sizeof(int));
	do
	{
		int m1=first_bit(len,a1);
		int kn=m1-m2;
		shift_l(len, kn, p1,c);
		if(cmp(len,a1,c)==-1)
		{
			kn--;
			shift_l(len, kn, p1, c);
		}
		raz(len,a1,c,a1);
	}
	while(cmp(len,a1,p1)!=-1);
	memcpy(a,a1,n1*sizeof(int));
	delete [] c;
	delete [] p1;
	delete [] a1;
}

// ������������ a �� b �� mod p
void mulp(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c)
{
	unsigned int * u11 = new unsigned int [2*len];

	umn(len, a, b, u11);
	mod_p(u11,2*len,p,len);
	memcpy(c,u11,len*sizeof(int));

	delete [] u11;
}

// ���������� � ������� �� mod p
void step_mod(unsigned int * p, unsigned int * a, int n1, unsigned int * b, int n2, unsigned int * c)
{
	unsigned int *c1 = new unsigned int [n1];
	unsigned int *buf = new unsigned int [2*n1];
	memset(c1,0,n1*sizeof(int));
	c1[0]=1;

	for(int i=n2-1;i>=0;i--)
		for(int j=BIT_INT-1;j>=0;j--)
		{
			mulp(n1,c1,c1,p,c1);
			if((b[i]>>j)&1)
				mulp(n1,c1,c1,p,c1);
		}

	memcpy(c,c1,n1*sizeof(int));
	delete [] c1;
	delete [] buf;
}

void shift_l(int n, int k, unsigned int * a, unsigned int * c)
{
	unsigned int x[MAXLEN];
	int n1 = k / BIT_INT;
	int n2 = k % BIT_INT;
	int i;
	for(i=0;i<n;i++) x[i] = 0;
	for(i=0;i<n;i++)
	{
		if(n2 && i+n1+1<n)
			x[i+n1+1]|=(a[i]>>(BIT_INT-n2));
		if(i+n1<n)
		{
			x[i+n1]|=(a[i]<<n2);
		}
	}
	for(i=0;i<n;i++) c[i] = x[i];
}

void shift_r(int n, int k, unsigned int * a, unsigned int * c)
{
	unsigned int x[MAXLEN];
	int n1 = k / BIT_INT;
	int n2 = k % BIT_INT;
	int i;
	for(i=0;i<n;i++) x[i] = 0;
	for(i=0;i<n;i++)
	{
		if(i-n1-1>=0)
		{
			x[i-n1-1]|=(a[i]<<(BIT_INT-n2));
		}
		if(i-n1>=0)
			x[i-n1]|=(a[i]>>n2);
	}
	for(i=0;i<n;i++) c[i] = x[i];
}

// c - �������� � a �� ������ N
// len - ����� ����� � ������
// ���������� -1, ���� �������� � ����, 0 - � ��������� �������
int obr(int len, unsigned int * a, unsigned int * N, unsigned int * c)
{
	int i;
	if(first_bit(len,a)==-1)
	{
		for(i=0; i<len; i++) c[i] = 0;
		return -1;
	}
	unsigned int v[MAXLEN];
	unsigned int u[MAXLEN];
	unsigned int v0[MAXLEN];
	unsigned int u0[MAXLEN];
	unsigned int q[MAXLEN];
	unsigned int x[MAXLEN*2];
	for(i=0; i<len; i++)
	{
		u0[i] = u[i] = 0;
		v0[i] = N[i];
		v[i] = a[i];
	}
	u[0]=1;
	div(len,N,a,q);
	int r;
	while((r= first_bit(len,v))>0)
	{
		for(i=0; i<len; i++) c[i] = v[i];
		umn(len,q,v,x);
		raz(len,v0,x,v);
		for(i=0; i<len; i++) v0[i] = c[i];

		for(i=0; i<len; i++) c[i] = u[i];
		umn(len,q,u,x);
		raz(len,u0,x,u);
		for(i=0; i<len; i++) u0[i] = c[i];

		div(len,v0,v,q);
	}
	if((u[len-1]>>(BIT_INT-1))&1)
		sum(len,u,N,c);
	else
		for(i=0; i<len; i++) c[i] = u[i];

	if(r==0)
		return 0;
	else
		return 1;
}

int div(int len, unsigned int * a, unsigned int * b, unsigned int * c)
{
	int sign1,sign2;
	int m1,m2,kn,i;
	unsigned int y[MAXLEN];
	unsigned int yb[MAXLEN];
	for(i=0;i<len;i++) {y[i] = a[i]; yb[i] = b[i];c[i] = 0;}
	if(first_bit(len,yb)==-1)
		return -1;
	sign1 = (y[len-1]>>(BIT_INT-1))&1;
	sign2 = (yb[len-1]>>(BIT_INT-1))&1;
	if(sign1)
		change_sign(len,y);
	if(sign2)
		change_sign(len,yb);
	if(cmp(len,y,yb)!=-1)
	{
		unsigned int x[MAXLEN];
		m2=first_bit(len,yb);
		do
		{
			m1=first_bit(len,y);
			kn=m1-m2;
			shift_l(len, kn, yb, x);
			if(cmp(len,y,x)==-1)
			{
				kn--;
				shift_l(len, kn, yb, x);
			}
			c[kn / BIT_INT]|=1<<(kn & (BIT_INT-1));
			raz(len,y,x,y);
		}
		while(cmp(len,y,yb)!=-1);
	}
	return 0;
}

void change_sign(int len, unsigned int * c)
{
	int i, p;
	unsigned int s;
	for (i = 0; i < len; i++)
		c[i] = ~c[i];
	if ((c[0] & 1) == 0)
		c[0] |= 1;
	else
	{
		i = 0;
		do
		{
			if (c[i] == -1)	p = 1;
			else	p = 0;
			c[i] += 1;
			i++;
		} while (p == 1 && i < len);
	}
}


