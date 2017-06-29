(function () {
    'use strict';

    app.controller('panicButtonCtrl', panicButtonController).directive('panicButton', panicButtonDirective);

    panicButtonController.$inject = ['$scope', '$resource'];

    function panicButtonController($scope, $resource) {

        $scope.panic = function() {
            $resource('car/stop').save({}, {},
                function (success) {
                    console.debug('panic signal send', success);
                },
                function (error) {
                    console.error('panic signal failed. REALLY a big problem if there is still a lifeline', error);
                });
        }
    }

    function panicButtonDirective() {
        return {
            templateUrl: './scripts/directives/panicButton/panicButton.html',
            controller: 'panicButtonCtrl',
            replace: true
        }
    }

})();