(function () {
    'use strict';

    app.controller('panicButtonCtrl', panicButtonController).directive('panicButton', panicButtonDirective);

    panicButtonController.$inject = ['$scope', '$resource'];

    function panicButtonController($scope, $resource) {

        $scope.panic = function() {
            $resource('car/mode/0').save({}, {},
                function (success) {
                    console.debug('stop signal send', success);
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