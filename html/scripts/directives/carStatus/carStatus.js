(function() {
    'use strict';

    app.controller('carStatusCtrl', carStatusController).directive('carStatus', carStatusDirective);

    carStatusController.$inject = ['$rootScope', '$scope','$resource', 'websocketFactory'];

    function carStatusController($rootScope, $scope, $resource, websocketFactory) {
        $scope.connected = false;
        $scope.modes = ['stopped','manual','autonomous'];

        var websocket = websocketFactory.create('car_status');

        // websocket.onMessage(function (message) {
        //     if (message.data !== 'pong') {
        //         console.log("Car: " + message.data);
        //         $scope.car = angular.fromJson(message.data);
        //         $rootScope.carMode = $scope.car.mode;
        //     }
        // });

        $scope.updateCarMode = function(carMode) {
            $resource($rootScope.hostName + 'car/mode/:mode').save({
                    mode: carMode
                }, {},
                function (data) {
                    $rootScope.car['mode'] = data.mode;
                    console.debug('mode send');
                },
                function (error) {
                    console.error('mode update failed', error);
                });
        };

        $scope.$on('$destroy', function () {
            console.debug('destroying carstatus controller');
            websocket.closeConnection();
        });

    }

    function carStatusDirective() {
        return {
            templateUrl: './scripts/directives/carStatus/carStatus.html',
            controller: 'carStatusCtrl',
            replace: true
        }
    }

})();