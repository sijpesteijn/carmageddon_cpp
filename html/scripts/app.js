'use strict';

var app = angular.module('carmageddon', [
    'ngCookies',
    'ngResource',
    'ngSanitize',
    'ngRoute',
    'ngWebSocket',
    'color.picker'
]);

app.run(function ($rootScope) {
    $rootScope.carMode = 'stopped';
    $rootScope.hostName = 'http://carmageddon.dev/'
    // $rootScope.settings = {
    //     throttleLimit: 40
    // }
});


app.factory('websocketFactory', function ($websocket, $location, $interval) {

    function websocket(endpoint) {
        var connection = null;
        var connected = false;
        var pinger;

        var url = 'ws://192.168.7.2:1984/' + endpoint;

        this.connect = function() {
            try {
                connection = $websocket(url, undefined, {
                    binaryType: "arraybuffer"
                });
            } catch (err) {
                console.log('Can\'t connect to ' + url + ', err: ' + err);
            }
        };

        this.connect();

        connection.onOpen(function () {
            connected = true;
            startPinger();
        });

        function startPinger() {
            pinger = $interval(function () {
                connection.send('ping');
            }, 100)
        }

        function stopPinger() {
            $interval.cancel(pinger);
        }

        connection.onError(function(error) {
            connected = false;
            stopPinger();
            console.log('Connection stopped' + error);
        });

        this.onMessage = function(callback) {
            connection.onMessage(function (message) {
                callback(message);
            })
        };

        this.sendMessage = function(message) {
            connection.send(message);
        };

        this.closeConnection = function() {
            connection.close();
            console.log('Connection closed');
        }
    }

    return {
        create: function (endpoint) {
            return new websocket(endpoint);
        }
    }

});

app.factory('settingsFactory', function($timeout, $resource, $q) {
    var updateTimeout = undefined;
    var newSettings;
    var settings = $q.defer();

    function getSettings() {
        $resource('./rest/settings').get({}, {},
            function (data) {
                settings.resolve(data);
            },
            function (error) {
                console.error('mode update failed', error);
            });
        return settings;
    }

    function updateSettings() {
        $resource('./rest/settings').save({},
            newSettings,
            function (success) {
            },
            function (error) {
                console.error('mode update failed', error);
            });
    }

    function delaySettingsUpdate(settings) {
        newSettings = settings;
        if (updateTimeout != undefined) {
            $timeout.cancel(updateTimeout);
        }
        updateTimeout = $timeout(updateSettings, 500);
    }


    return {
        getSettings: function () {
            return getSettings().promise;
        },
        updateSettings: function (settings) {
            delaySettingsUpdate(settings);
        }
    }
});