#!/bin/bash

# =========================
# 1. EVEN ODD FILE SEPARATION
# =========================
> even
> odd

while read n
do
    if [ $((n % 2)) -eq 0 ]
    then
        echo $n >> even
    else
        echo $n >> odd
    fi
done < numbers


# =========================
# 2. SMALLEST FILE NAME
# =========================
min=""

for f in *
do
    if [ -f "$f" ]
    then
        if [ -z "$min" ] || [ ${#f} -lt ${#min} ]
        then
            min=$f
        fi
    fi
done

echo "Smallest file: $min"


# =========================
# 3. SORT ARRAY
# =========================
echo "Enter numbers:"
read -a arr

for ((i=0;i<${#arr[@]};i++))
do
    for ((j=0;j<${#arr[@]}-i-1;j++))
    do
        if [ ${arr[j]} -gt ${arr[$((j+1))]} ]
        then
            temp=${arr[j]}
            arr[j]=${arr[$((j+1))]}
            arr[$((j+1))]=$temp
        fi
    done
done

echo "Sorted array: ${arr[@]}"


# =========================
# 4. BASIC LINUX COMMANDS TASKS
# =========================
ls > outfile
grep "[0-9]" file.txt > list
chmod u+x test
chmod g-w test
alias rm='rm -i'
who | wc -l


# =========================
# 5. FILE OPS + LINKS + CUT + WC
# =========================
ls -a > hidden
chmod u+w test
chmod o-x test

ln file softlink
ln file hardlink

tr 'a-z' 'A-Z' < file.txt

cut -c1,10 file.txt

sort file.txt | uniq -c


# =========================
# 6. PRIME + REVERSE NUMBER
# =========================
echo "Enter number:"
read n

prime=1
for ((i=2;i<=n/2;i++))
do
    if [ $((n%i)) -eq 0 ]
    then
        prime=0
        break
    fi
done

if [ $prime -eq 1 ]
then
    echo "Prime"
else
    echo "Not Prime"
fi

rev=0
temp=$n

while [ $temp -gt 0 ]
do
    r=$((temp%10))
    rev=$((rev*10+r))
    temp=$((temp/10))
done

echo "Reverse: $rev"


# =========================
# 7. SUBSTRING COUNT
# =========================
echo "Enter string:"
read str
echo "Enter substring:"
read sub

count=$(echo "$str" | grep -o "$sub" | wc -l)
echo "Occurrences: $count"


# =========================
# 8. DECIMAL TO BINARY
# =========================
echo "Enter number:"
read n

bin=""
temp=$n

while [ $temp -gt 0 ]
do
    r=$((temp%2))
    bin="$r$bin"
    temp=$((temp/2))
done

echo "Binary: $bin"


# =========================
# 9. STUDENT GRADE SYSTEM
# =========================
echo "Enter name:"
read name
echo "Enter marks:"
read m1 m2 m3

total=$((m1+m2+m3))
per=$((total/3))

echo "Total: $total"
echo "Percentage: $per"

if [ $per -ge 70 ]
then
    echo "First Class"
elif [ $per -ge 50 ]
then
    echo "Second Class"
elif [ $per -ge 35 ]
then
    echo "Pass"
else
    echo "Fail"
fi


# =========================
# 10. SUM OF EVEN NUMBERS
# =========================
sum_even() {
    n=$1
    sum=0
    for ((i=1;i<=n;i++))
    do
        if [ $((i%2)) -eq 0 ]
        then
            sum=$((sum+i))
        fi
    done
    echo "Sum of even numbers: $sum"
}

echo "Enter limit:"
read n
sum_even $n