import time
import unittest
from subprocess import Popen, PIPE

import scipy.integrate as spi
import numpy as np


f = lambda x : np.sqrt(1 + np.exp(x))

def calculateIntegral(a: float, b: float, n: int, f: callable):
    theta = np.linspace(a, b, num=n)
    result = spi.trapezoid(f(theta), x=theta)
    return round(result, 7)


TEST_PROGRAM = './task6 '

class TestClassTask(unittest.TestCase):

    def callPopen(self, message):
        with Popen(TEST_PROGRAM + message, stdout=PIPE, stderr=PIPE, shell=True) as process:
            timeStarted = time.time()
            process.wait()
            timeDelta = time.time() - timeStarted 
            assert process.returncode == 0
            return process.stdout.read().rstrip(), timeDelta


    def test_simple_integral(self):
        a, b, n, tn = (
            0,
            2,
            10_000_000,
            1,
        )
        TEST_ARGS = f'{a} {b} {n} {tn}'

        process_out, _ = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_output = calculateIntegral(a, b, n, f)
        print(f"process integral output = {process_out} real integral value = {expected_output}")
        self.assertAlmostEqual(float(process_out), float(expected_output), 4)


    def test_accuracy_integral_for_threads(self):
        a, b, n, tn = (
            0,
            1,
            10_000,
            10,
        )
        TEST_ARGS = f'{a} {b} {n} {tn}'

        process_out, _ = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_output = calculateIntegral(a, b, n, f)
        print(f"process integral output = {process_out} real integral value = {expected_output}")
        self.assertAlmostEqual(float(process_out), float(expected_output), 3)


    def test_accuracy_integral_for_max_range(self):
        a, b, n, tn = (
            0,
            50,
            10_000_000,
            1,
        )
        TEST_ARGS = f'{a} {b} {n} {tn}'

        process_out, _ = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_output = calculateIntegral(a, b, n, f)
        print(f"process integral output = {process_out} real integral value = {expected_output}")
        self.assertAlmostEqual(float(process_out), float(expected_output), delta=0.1)


    def test_accuracy_integral_for_max_range_for_threads(self):
        a, b, n, tn = (
            0,
            50,
            10_000_000,
            10,
        )
        TEST_ARGS = f'{a} {b} {n} {tn}'

        process_out, _ = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_output = calculateIntegral(a, b, n, f)
        print(f"process integral output = {process_out} real integral value = {expected_output}")
        self.assertAlmostEqual(float(process_out), float(expected_output), delta=0.1)



    def test_accuracy_integral(self):
        a, b, n, tn = (
            0,
            1,
            10_000,
            1,
        )
        TEST_ARGS = f'{a} {b} {n} {tn}'

        process_out, _ = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_output = calculateIntegral(a, b, n, f)

        print(f"process integral output = {process_out} real integral value = {expected_output}")
        self.assertAlmostEqual(float(process_out), float(expected_output), 3)


    def test_correctnes_many_threads(self):
        a, b, n, tn = (
            0,
            1,
            1_000_000,
            10,
        )
        TEST_ARGS = f'{a} {b} {n} {tn}'

        process_out, _ = self.callPopen(TEST_ARGS)
        # Check stdout
        expected_output = calculateIntegral(a, b, n, f)

        print(f"process integral for many threads output = {process_out} real integral value = {expected_output}")
        self.assertAlmostEqual(float(process_out), float(expected_output), 3)


    def test_simple_threads_time(self):
        experiments_count = 10
        a, b, n, tn = (
            0,
            2,
            5_000_000,
            1,
        )
        TEST_ARGS = f'{a} {b} {n} {tn}'

        time_delta_1_thread_all = 0.0
        for _ in range(experiments_count):
            _, time_delta_1_thread = self.callPopen(TEST_ARGS)
            time_delta_1_thread_all += time_delta_1_thread
        time_delta_1_thread_all /= experiments_count


        tn = 2
        TEST_ARGS = f'{a} {b} {n} {tn}'

        time_delta_2_thread_all = 0.0
        for _ in range(experiments_count):
            _, time_delta_2_thread = self.callPopen(TEST_ARGS)
            time_delta_2_thread_all += time_delta_2_thread
        time_delta_2_thread_all /= experiments_count

        print(f"time delta: 1 thread = {time_delta_1_thread_all} seconds, 2 threads = {time_delta_2_thread_all} seconds")
        print(f"(1 thread)/(2 threads) time = {time_delta_1_thread_all / time_delta_2_thread_all} times")
        self.assertTrue(time_delta_2_thread_all < time_delta_1_thread_all)



if __name__ == '__main__':
    unittest.main()