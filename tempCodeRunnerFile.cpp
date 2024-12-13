    struct tm * datetime;

    time(&timestamp);
    datetime = localtime(&timestamp);

    strftime(output, 50, "%B %e, %Y", datetime);
    cout << output << "\n";

    strftime(output, 50, "%I:%M:%S %p", datetime);
    cout << output << "\n";

    strftime(output, 50, "%D", datetime);
    cout << output << "\n";

    strftime(output, 50, "%c", datetime);
    cout << output << "\n";