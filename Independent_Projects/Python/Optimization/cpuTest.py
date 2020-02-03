import time

def cpu_bound(num):
    return sum(i*i for i in range(num))

def find_sums(nums):
    for num in nums:
        cpu_bound(num)


numbers=[5_000_000 + x for x in range(20)]

start_time=time.time()
find_sums(numbers)
duration=time.time()-start_time
print(f"Duration {duration} seconds")
