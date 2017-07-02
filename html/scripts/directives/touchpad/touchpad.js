(function () {
    'use strict';

    app.controller('touchpadCtrl', touchpadController).directive('touchpad', touchpadDirective);

    touchpadController.$inject = ['$rootScope', '$scope', '$resource', '$interval', 'settingsFactory'];

    function touchpadController($rootScope, $scope, $resource, $interval, settingsFactory) {
        $scope.show = false;
        $scope.settings = 0;

        settingsFactory.getSettings().then(function (data) {
            $scope.settings = data;
        });

        var joystick = new VirtualJoystick({
            container: document.getElementById('touchpad'),
            baseX: 400,
            baseY: 400,
            mouseSupport: true,
            limitStickTravel: true,
            stickRadius: 150
        });

        function postThrottle(throttle) {
            console.log(throttle + ' ' + JSON.stringify($rootScope.car));
            $resource('car/engine/:throttle').save({
                throttle: throttle
            }, {},
            function (success) {
                // console.debug('throttle send', success);
            },
            function (error) {
                console.error('throttle update failed', error);
            });
        }

        function postAngle(angle) {
            console.log(angle + ' ' + JSON.stringify($rootScope.car));
            $resource('car/steer/:angle').save({
                angle: angle
            }, {},
            function (success) {
                // console.debug('angle send', success);
            },
            function (error) {
                console.error('angle update failed', error);
            });
        }

        $interval(function () {
            var currAngle = Math.round(joystick.deltaX()/3);
            var currThrottle = -1 * Math.round(joystick.deltaY()/3);
            if (currAngle != $rootScope.car.angle) {
                postAngle(currAngle);
                $rootScope.car.angle = currAngle;
            }
            if (currThrottle > $scope.settings.maxThrottle) {
                currThrottle = $scope.settings.maxThrottle;
            } else if (currThrottle < -$scope.settings.maxThrottle) {
                currThrottle = -$scope.settings.maxThrottle;
            } 
            if (currThrottle != $rootScope.car.throttle) {
                postThrottle(currThrottle);
                $rootScope.car.throttle = currThrottle;
            }
        }, 1 / 30 * 1000);

        $scope.updateMaxThrottle = function () {
            settingsFactory.updateSettings($scope.settings);
        }
    }

    function touchpadDirective() {
        return {
            templateUrl: './scripts/directives/touchpad/touchpad.html',
            controller: 'touchpadCtrl',
            replace: true
        }
    }

})();