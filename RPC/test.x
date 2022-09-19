struct path {
    string value <256>;
};

program TEST {
    version TEST_1 {
        int FUNC(path) = 1;
    } = 1;
} = 0x20000001;
