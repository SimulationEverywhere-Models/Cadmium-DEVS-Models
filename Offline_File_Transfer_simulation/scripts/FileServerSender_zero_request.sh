echo "Running test scenario for FileServerSender atomic model when there is no request. i.e zero"
cd ../bin

./FILESERVERSENDER_TEST ../input_data/NoRequest.txt ../input_data/fileserversender_dataIn_test.txt ../input_data/fileserversender_ackIn_test.txt
