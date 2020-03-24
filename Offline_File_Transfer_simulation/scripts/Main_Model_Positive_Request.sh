echo "Running the main model test scenario when there is a request for download. i.e positive requestIn. Also, controlIn,i.e.Number of packets sent, can be negative, zero or positive."
cd ../bin

./OFFLINE_FILE_TRANSFER ../input_data/controlIn.txt ../input_data/requestIn.txt 
