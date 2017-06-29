(function() {
    'use strict';

    app.controller('lifelineCtrl', lifelineController).directive('lifeline', lifelineDirective);

    lifelineController.$inject = ['$rootScope', '$scope', 'websocketFactory'];

    function lifelineController($rootScope, $scope, websocketFactory) {
        $scope.heartbeat = false;
        var websocket = websocketFactory.create('lifeline');

        websocket.onMessage(function(message) {
            if (message.data != 'ping') {
                console.log(message.data);
                $rootScope.car = message.data;
            }
            $scope.heartbeat = !$scope.heartbeat;
        });

        $scope.$on('$destroy', function () {
            console.debug('destroying lifeline controller');
            websocket.closeConnection();
        });

    }

    function lifelineDirective() {
        return {
            templateUrl: './scripts/directives/lifeline/lifeline.html',
            controller: 'lifelineCtrl',
            replace: true
        }
    }

})();