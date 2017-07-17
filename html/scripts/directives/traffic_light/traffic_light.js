(function () {
    'use strict';

    app.controller('traffic_lightCtrl', traffic_lightController).directive('trafficLight', traffic_lightDirective);

    traffic_lightController.$inject = ['$rootScope', '$scope', '$resource'];

    function traffic_lightController($rootScope, $scope, $resource) {
    	$scope.settings;

    	function loadSettings() {
	        $resource('observer/type/traffic_light').get({}, {},
            function (data) {
                $scope.settings = data;
            },
            function (error) {
                console.error('mode update failed', error);
            });
		}

		loadSettings();
	}

    function traffic_lightDirective() {
        return {
            templateUrl: './scripts/directives/traffic_light/traffic_light.html',
            controller: 'traffic_lightCtrl',
            replace: true
        }
    }

})();