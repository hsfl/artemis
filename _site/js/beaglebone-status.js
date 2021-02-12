function checkStatus() {
    var windows_options = {
        host: '192.168.7.2',
        port: 80,
        path: '/index.html'
    };
    var linux_options = {
        host: '192.168.6.2',
        port: 80,
        path: '/index.html'
    };
    var windows_status = document.getElementByID("bbb_windows");
    var linux_status = document.getElementByID("bbb_linux");
    http.get(windows_options, function(res) {
        if (res.statusCode == 200) {
            windows_status.style.backgroundColor = 'green';
        }
        else {
            windows_status.style.backgroundColor = 'red';
        }
    }).on('error', function(e) {
        windows_status.style.backgroundColor = 'red';
    });
    http.get(linux_options, function(res) {
        if (res.statusCode == 200) {
            linux_status.style.backgroundColor = 'green';
        }
        else {
            linux_status.style.backgroundColor = 'red';
        }
    }).on('error', function(e) {
        linux_status.style.backgroundColor = 'red';
    });
}
setInterval(checkStatus, 5);