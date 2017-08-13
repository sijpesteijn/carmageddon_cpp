import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ManualComponent } from './manual.component';
import { RouterModule } from '@angular/router';
import { manual_routes } from './manual.routes';
@NgModule({
    imports: [
        CommonModule,
        RouterModule.forChild(manual_routes)
    ],
    declarations: [
        ManualComponent
    ]
})
export class ManualModule {

}