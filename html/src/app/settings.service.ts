import { Injectable, Inject } from '@angular/core';
import { Http } from '@angular/http';
import { Observable } from 'rxjs/Rx';

@Injectable()
export class SettingsService {

    private settingsData: Observable<any>;

    constructor(private http: Http, @Inject('settings.path') private path: string) {
    }

    get(key: string) {
        return this.getData().map(data => {
            let keys = key.split('.');
            let result = data;
            keys.forEach((k) => result = result[k]);
            return result;
        });
    }

    private getData() {
        if (!this.settingsData) {
            this.settingsData = this.http.get(this.path)
                .map(res => res.json()); //.publishLast().refCount();
        }
        return this.settingsData;
    }
}
