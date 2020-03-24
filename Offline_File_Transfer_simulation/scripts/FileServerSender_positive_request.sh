echo "Running test scenario for FilseServerSender atomic model when there is positive requests to download file"
cd ../bin

./FILESERVERSENDER_TEST ../input_data/fileserversender_requestIn_test.txt ../input_data/fileserversender_dataIn_test.txt ../input_data/fileserversender_ackIn_test.txt
